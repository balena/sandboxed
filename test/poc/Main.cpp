/** @file Main.cpp
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 2/3/2010 11:50:45
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "stdafx.h"
#include "Window.h"

#include <tchar.h>
#include <shellapi.h>

#include <sstream>
#include <base/at_exit.h>
#include <base/logging.h>
#include <base/message_loop.h>
#include <base/command_line.h>
#include <base/thread.h>
#include <sandbox/src/sandbox.h>
#include <sandbox/src/sandbox_factory.h>
#include <chrome/common/ipc_channel_proxy.h>
#include <chrome/common/ipc_message_utils.h>

struct PocMsg_Its_Alive {
    int32 anInteger;
    std::string aString;
    std::wstring aWString;
    bool aBoolean;
    base::Time aTime;
};

namespace IPC {

template <>
struct ParamTraits<PocMsg_Its_Alive> {
    typedef PocMsg_Its_Alive param_type;
    static void Write(Message* m, const param_type& p) {
        WriteParam(m, p.anInteger);
        WriteParam(m, p.aString);
        WriteParam(m, p.aWString);
        WriteParam(m, p.aBoolean);
        WriteParam(m, p.aTime);
    }
    static bool Read(const Message* m, void** iter, param_type* p) {
        return
            ReadParam(m, iter, &p->anInteger) &&
            ReadParam(m, iter, &p->aString) &&
            ReadParam(m, iter, &p->aWString) &&
            ReadParam(m, iter, &p->aBoolean) &&
            ReadParam(m, iter, &p->aTime);
    }
    static void Log(const param_type& p, std::wstring* l) {
        l->append(L"(");
        LogParam(p.anInteger, l);
        l->append(L", ");
        LogParam(p.aString, l);
        l->append(L", ");
        LogParam(p.aWString, l);
        l->append(L", ");
        LogParam(p.aBoolean, l);
        l->append(L", ");
        LogParam(p.aTime, l);
        l->append(L")");
    }
};

} // namespace IPC

class ChannelListener : public IPC::Channel::Listener
{
public:
    virtual void OnMessageReceived(const IPC::Message& message) {
        PocMsg_Its_Alive p;
        void* iter = NULL;
        IPC::ParamTraits<PocMsg_Its_Alive>::Read(&message, &iter, &p);

        std::wstring log;
        IPC::ParamTraits<PocMsg_Its_Alive>::Log(p, &log);

        ::MessageBox(NULL, log.c_str(), L"Target: Received message", 0);
    }

    virtual void OnChannelError() {
    }
};

void AddDebugMessage(const wchar_t* format, ...);

CAppModule _Module;

int APIENTRY _tWinMain(HINSTANCE instance, HINSTANCE, wchar_t* command_line,
                       int show_command)
{
    UNREFERENCED_PARAMETER(command_line);

    _Module.Init(NULL, instance);

    base::AtExitManager exit_manager;
    CommandLine::Init(0, NULL);
    MessageLoop loop(MessageLoop::TYPE_IO);

    sandbox::BrokerServices* broker_service =
        sandbox::SandboxFactory::GetBrokerServices();
    sandbox::ResultCode result;

    // This application starts as the broker; an application with a UI that
    // spawns an instance of itself (called a 'target') inside the sandbox.
    // Before spawning a hidden instance of itself, the application will have
    // asked the user which DLL the spawned instance should load and passes
    // that as command line argument to the spawned instance.
    //
    // We check here to see if we can retrieve a pointer to the BrokerServices,
    // which is not possible if we are running inside the sandbox under a
    // restricted token so it also tells us which mode we are in. If we can
    // retrieve the pointer, then we are the broker, otherwise we are the target
    // that the broker launched.
    if (NULL != broker_service) {
        // Yes, we are the broker so we need to initialize and show the UI
        if (0 != (result = broker_service->Init())) {
            ::MessageBox(NULL, L"Failed to initialize the BrokerServices object",
                         L"Error during initialization", MB_ICONERROR);
            return 1;
        }

        wchar_t exe_name[MAX_PATH];
        if (0 == GetModuleFileName(NULL, exe_name, MAX_PATH - 1)) {
            ::MessageBox(NULL, L"Failed to get name of current EXE",
                         L"Error during initialization", MB_ICONERROR);
            return 1;
        }

        sandbox::TargetPolicy* policy = broker_service->CreatePolicy();
        policy->SetJobLevel(sandbox::JOB_LOCKDOWN,
                            JOB_OBJECT_UILIMIT_HANDLES|
                            JOB_OBJECT_UILIMIT_READCLIPBOARD|
                            JOB_OBJECT_UILIMIT_WRITECLIPBOARD);
        policy->SetTokenLevel(sandbox::USER_RESTRICTED_SAME_ACCESS,
                              sandbox::USER_LIMITED);
        //policy->SetAlternateDesktop(false);
        policy->SetDelayedIntegrityLevel(sandbox::INTEGRITY_LEVEL_LOW);

        PROCESS_INFORMATION target;
        sandbox::ResultCode result = broker_service->SpawnTarget(exe_name,
                                                                 L"", policy,
                                                                 &target);
        policy->Release();
        policy = NULL;

        bool return_value = false;
        if (sandbox::SBOX_ALL_OK != result) {
            AddDebugMessage(
                L"Failed to spawn target %ls w/args (%ls), sandbox error code: %d",
                exe_name, L"", result);
            return_value = false;
        }

        // The thread needs to out-live the ChannelProxy.
        base::Thread thread("BrokerChannel");
        base::Thread::Options options;
        options.message_loop_type = MessageLoop::TYPE_IO;
        thread.StartWithOptions(options);

        std::ostringstream ss;
        ss << target.dwProcessId;

        // setup IPC channel proxy
        ChannelListener listener;
        IPC::ChannelProxy *channel =  new IPC::ChannelProxy(ss.str(), IPC::Channel::MODE_SERVER,
                                  &listener, NULL, thread.message_loop());

        ::ResumeThread(target.hThread);
        ::CloseHandle(target.hThread);

        // Send Message
        IPC::Message *msg = 
            new IPC::Message(1, 2, IPC::Message::PRIORITY_NORMAL);

        PocMsg_Its_Alive p;
        p.anInteger = 666;
        p.aString = "It's alive!";
        p.aWString = L"It's alive again!";
        p.aBoolean = true;
        p.aTime = base::Time::Now();

        IPC::ParamTraits<PocMsg_Its_Alive>::Write(msg, p);

        std::wstring log;
        IPC::ParamTraits<PocMsg_Its_Alive>::Log(p, &log);

        ::MessageBox(NULL, log.c_str(), L"Broker: Sending message", 0);
        channel->Send(msg);

        Window wnd;
        wnd.CreateAndLoop(L"Broker WTL Window", show_command);

        // cleanup child process
        broker_service->WaitForAllTargets();

        delete channel;
        thread.Stop();
    }
    else {
        // This is an instance that has been spawned inside the sandbox by the
        // broker, so we need to parse the command line to figure out which DLL to
        // load and what entry point to call
        sandbox::TargetServices* target_service
            = sandbox::SandboxFactory::GetTargetServices();

        if (NULL == target_service) {
            // TODO(finnur): write the failure to the log file
            // We cannot display messageboxes inside the sandbox unless access to
            // the desktop handle has been granted to us, and we don't have a
            // console window to write to. Therefore we need to have the broker
            // grant us access to a handle to a logfile and write the error that
            // occurred into the log before continuing
            return -1;
        }

        // Debugging the spawned application can be tricky, because DebugBreak()
        // and _asm int 3 cause the app to terminate (due to a flag in the job
        // object), MessageBoxes() will not be displayed unless we have been granted
        // that privilege and the target finishes its business so quickly we cannot
        // attach to it quickly enough. Therefore, you can uncomment the
        // following line and attach (w. msdev or windbg) as the target is sleeping
        //Sleep(10000);

        if (sandbox::SBOX_ALL_OK != (result = target_service->Init())) {
            // TODO(finnur): write the initialization error to the log file
            return -2;
        }

        // The thread needs to out-live the ChannelProxy.
        base::Thread thread("TargetChannel");
        base::Thread::Options options;
        options.message_loop_type = MessageLoop::TYPE_IO;
        thread.StartWithOptions(options);

        std::ostringstream ss;
        ss << ::GetCurrentProcessId();

        // setup IPC channel proxy
        ChannelListener listener;
        IPC::ChannelProxy channel(ss.str(), IPC::Channel::MODE_CLIENT,
                                  &listener, NULL, thread.message_loop());

        target_service->LowerToken();

        Window wnd;
        wnd.CreateAndLoop(L"Target WTL Window", show_command);

        thread.Stop();
    }

    _Module.Term();
    return 0;
}

void AddDebugMessage(const wchar_t* format, ...)
{

}

/* Modeline for vim: set tw=79 et ts=4: */

