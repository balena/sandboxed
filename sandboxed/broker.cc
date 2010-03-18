/** @file broker.cc
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 1/3/2010 11:40:58
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <sandboxed/broker.h>
#include <sandboxed/target_process_internal.h>
#include <chrome/common/ipc_channel_proxy.h>
#include <base/thread.h>
#include <sandbox/src/sandbox_factory.h>
#include <sandbox/src/win_utils.h>
#include <vector>

namespace sandboxed {

static int cWaitProcessTimeOut = 100;

class BrokerImpl : public Broker,
                   public sandbox::SingletonBase<BrokerImpl>
{
public:
    BrokerImpl();
    virtual ~BrokerImpl();

    virtual TargetProcess *spawnTarget(const wchar_t *arguments);

    virtual bool peekTargets(TargetProcess **process);

    virtual TargetProcess *waitForTargets();
    virtual void wakeup();

protected:
    sandbox::BrokerServices *mBrokerService;
    std::vector<TargetProcessImpl *> mTargetProcesses;
    HANDLE mWakeupEvent;

    bool checkAllTargets(DWORD aTimeOut, DWORD *aResult);

    DISALLOW_EVIL_CONSTRUCTORS(BrokerImpl);
};

bool isBroker() {
    sandbox::BrokerServices* broker_service =
        sandbox::SandboxFactory::GetBrokerServices();
    return broker_service ? true : false;
}

Broker* Broker::instance() {
    if (!isBroker())
        return 0;
    return BrokerImpl::GetInstance();
}

BrokerImpl::BrokerImpl() {
    mBrokerService = sandbox::SandboxFactory::GetBrokerServices();
    if (mBrokerService->Init() != 0) {
        ::MessageBox(NULL, L"Failed to initialize the BrokerServices object",
                           L"Error during initialization", MB_ICONERROR);
    }
    mWakeupEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (mWakeupEvent == NULL){
        ::MessageBox(NULL, L"Failed to Create the WakeupEvent",
                           L"Error during initialization", MB_ICONERROR);
    }
}

BrokerImpl::~BrokerImpl() {
    CloseHandle(mWakeupEvent);
}

TargetProcess *BrokerImpl::spawnTarget(const wchar_t *arguments) {
    wchar_t exe_name[MAX_PATH];
    if (0 == GetModuleFileName(NULL, exe_name, MAX_PATH - 1)) {
        ::MessageBox(NULL, L"Failed to get name of current EXE",
                     L"Error during initialization", MB_ICONERROR);
        return 0;
    }

    sandbox::TargetPolicy* policy = mBrokerService->CreatePolicy();
    policy->SetJobLevel(sandbox::JOB_LOCKDOWN,
                        JOB_OBJECT_UILIMIT_HANDLES|
                        JOB_OBJECT_UILIMIT_READCLIPBOARD|
                        JOB_OBJECT_UILIMIT_WRITECLIPBOARD);
    policy->SetTokenLevel(sandbox::USER_RESTRICTED_SAME_ACCESS,
                          sandbox::USER_LIMITED);
    policy->SetDelayedIntegrityLevel(sandbox::INTEGRITY_LEVEL_LOW);

    sandbox::ResultCode result;
    PROCESS_INFORMATION target = {0};
    result = mBrokerService->SpawnTarget(exe_name, arguments, policy, &target);
    policy->Release();
    if (result != sandbox::SBOX_ALL_OK)
        return 0; // TODO error!

    TargetProcessImpl *inst = new TargetProcessImpl(target.hProcess);
    mTargetProcesses.push_back(inst);

    ResumeThread(target.hThread);
    CloseHandle(target.hThread);

    return inst;
}

bool BrokerImpl::peekTargets(TargetProcess **process) {
    DWORD result;

    // Check for all targets
    if (checkAllTargets(0, &result)){
        DWORD index = result - WAIT_OBJECT_0;
        if (index == 0) // Wakeup Event
            *process = 0;
        else {
            // Get the process
            *process = mTargetProcesses.at(index-1);
            mTargetProcesses.erase(mTargetProcesses.begin()+index-1);
        }
        return true;
    }

    *process = 0;
    return false;
}

TargetProcess *BrokerImpl::waitForTargets() {
    DWORD result;

    // Wait for a process event or a wakeup
    while(!checkAllTargets(cWaitProcessTimeOut, &result));

    DWORD index = result - WAIT_OBJECT_0;
    if (index == 0) // Wakeup Event
        return 0;

    // Get the process
    TargetProcessImpl *process = mTargetProcesses.at(index-1);
    mTargetProcesses.erase(mTargetProcesses.begin()+index-1);

    return process;
}

bool BrokerImpl::checkAllTargets(DWORD aTimeOut, DWORD *aResult)
{
    HANDLE handles[MAXIMUM_WAIT_OBJECTS];
    DWORD nCount, nPos = 0;

    while(1) {
        if (nPos == mTargetProcesses.size())
            break;

        // Setup process handle array
        handles[0] = mWakeupEvent; // The first one is the wakeup event
        for (nCount = 0; nPos+nCount < mTargetProcesses.size(); nCount++) {
            if (nCount == MAXIMUM_WAIT_OBJECTS-1)
                break;
            handles[nCount+1] = mTargetProcesses.at(nPos+nCount)->getProcess();
        }
        nPos += nCount; // increment the handle 'window'

        *aResult = WaitForMultipleObjects(nCount+1,  // Number of object handles to wait for
                                         handles,   // Pointer to an array of object handles
                                         false,     // Wait for all process
                                         aTimeOut); // Time-out interval, in milliseconds
        if (*aResult == WAIT_TIMEOUT)
            continue;
        else
            return true;
    }

    return false;
}

void BrokerImpl::wakeup() {
    if (!SetEvent(mWakeupEvent))
        ::MessageBox(NULL, L"Failed to Set Event", L"Error during wakeup", MB_ICONERROR);
}

} // namespace sandboxed

/* Modeline for vim: set tw=79 et ts=4: */

