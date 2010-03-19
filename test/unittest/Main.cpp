/** @file Main.cpp
    @author Samuel Macedo <samuel@comunip.com.br>
    @date 2/3/2010 11:50:45
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifdef _HAS_TR1
#undef _HAS_TR1
#define _HAS_TR1 1
#endif

#include <sandboxed/platform.h>
#include <sandboxed/broker.h>
#include <sandboxed/target.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#pragma data_seg(".shared")
LONG lRun = 0;
#pragma data_seg()
#pragma comment(linker, "/section:.shared,rws")

namespace {

DWORD WINAPI waitForTargets_Thread(LPVOID lpParam) {
    sandboxed::TargetProcess *returning_process =
        sandboxed::Broker::instance()->waitForTargets();
    return 0;
}

sandboxed::TargetPolicy* createDefaultPolicy() {
    sandboxed::TargetPolicy *policy =
        sandboxed::Broker::instance()->createPolicy();
    policy->SetJobLevel(sandbox::JOB_LOCKDOWN,
                        JOB_OBJECT_UILIMIT_HANDLES|
                        JOB_OBJECT_UILIMIT_READCLIPBOARD|
                        JOB_OBJECT_UILIMIT_WRITECLIPBOARD);
    policy->SetTokenLevel(sandbox::USER_RESTRICTED_SAME_ACCESS,
                          sandbox::USER_LIMITED);
    policy->SetDelayedIntegrityLevel(sandbox::INTEGRITY_LEVEL_LOW);
    return policy;
}

sandboxed::TargetProcess *spawnTarget() {
    sandboxed::TargetPolicy *policy = createDefaultPolicy();
    sandboxed::TargetProcess *process =
        sandboxed::Broker::instance()->spawnTarget(L"", policy);
    policy->Release();
    return process;
}

} // empty namespace

TEST(Sandboxed_Broker, SpawnSimple) {
    sandboxed::TargetProcess *process = spawnTarget();
    ASSERT_TRUE(process);

    process->client()->waitForConnection();

    bool result = RPC::ClientCall<bool()>("endProcess")(process->client());
    ASSERT_EQ(result, true);

    sandboxed::TargetProcess *returning_process =
        sandboxed::Broker::instance()->waitForTargets();
    ASSERT_EQ(returning_process, process);
    delete returning_process;
}

TEST(Sandboxed_Broker, PeekTargets) {
    LONG last = lRun;
    
    sandboxed::TargetProcess *process, *returning_process;
   
    process = spawnTarget();
    ASSERT_TRUE(process);

    process->client()->waitForConnection();
    ASSERT_EQ(lRun, last+1);

    bool result = RPC::ClientCall<bool()>("endProcess")(process->client());
    ASSERT_EQ(result, true);

    while(1) {
        if (sandboxed::Broker::instance()->peekTargets(&returning_process))
            break;
        Sleep(100);
    }

    ASSERT_EQ(returning_process, process);
    delete returning_process;
}

TEST(Sandboxed_Broker, Thread) {
    LONG last = lRun;

    sandboxed::TargetProcess *process = spawnTarget();
    ASSERT_TRUE(process);

    process->client()->waitForConnection();
    ASSERT_EQ(lRun, last+1);

    HANDLE hThread;
    DWORD dwThreadId;
    hThread = CreateThread(NULL, 0, waitForTargets_Thread, process, 0, &dwThreadId);
    sandboxed::Broker::instance()->wakeup();

    DWORD dwRes = WaitForSingleObject(hThread, 1000);
    ASSERT_EQ(dwRes, WAIT_OBJECT_0);
    ::CloseHandle(hThread);

    bool result = RPC::ClientCall<bool()>("endProcess")(process->client());
    ASSERT_EQ(result, true);

    // Get the process
    sandboxed::TargetProcess *returning_process = 
            sandboxed::Broker::instance()->waitForTargets();
    ASSERT_EQ(process, returning_process);
    delete returning_process;
}

TEST(Sandboxed_Broker, VoidFunc) {
    
    // Create a new process
    sandboxed::TargetProcess *process = spawnTarget();
    ASSERT_TRUE(process);
    process->client()->waitForConnection();

    RPC::ClientCall<void()> voidfunc("voidfunc");

    LONG last = lRun;
    voidfunc(process->client());
    ASSERT_EQ(lRun, last+1);

    RPC::ClientCall<bool()> endProcess("endProcess");
    endProcess(process->client()); // end_process

    // Get the process->client()
    sandboxed::TargetProcess *returning_process = 
            sandboxed::Broker::instance()->waitForTargets();
    ASSERT_TRUE(returning_process);
    delete returning_process;
}

TEST(Sandboxed_Broker, Message) {
    
    // Create a new process
    sandboxed::TargetProcess *process = spawnTarget();
    ASSERT_TRUE(process);

    process->client()->waitForConnection();

    RPC::ClientCall<int()> one("one");
    RPC::ClientCall<bool()> True("True");
    RPC::ClientCall<bool()> False("False");
    RPC::ClientCall<double()> pi("pi");
    RPC::ClientCall<int(int)> identity("identity");
    RPC::ClientCall<double(int)> as_double("as_double");
    RPC::ClientCall<int(int, int)> muli("muli");
    RPC::ClientCall<double(double, double)> mulf("mulf");
    RPC::ClientCall<std::string(int)> print_int("print_int");
    RPC::ClientCall<std::string(std::vector<int>)> print_list("print_list");
    RPC::ClientCall<std::wstring(double)> print_wide("print_wide");
    RPC::ClientCall<int(int,int,int)> sum3("sum3");
    RPC::ClientCall<int(int,int,int,int)> sum4("sum4");
    RPC::ClientCall<int(int,int,int,int,int)> sum5("sum5");
    RPC::ClientCall<std::vector<int>(int, int, int, int)> list("list");
    RPC::ClientCall<bool()> endProcess("endProcess");

    // Call all functions
    ASSERT_EQ(one(process->client()), 1);
    ASSERT_EQ(True(process->client()), true);
    ASSERT_EQ(False(process->client()), false);
    ASSERT_EQ(pi(process->client()), 3.14);

    ASSERT_EQ(identity(process->client(), 1), 1);
    ASSERT_EQ(identity(process->client(), 65535), 65535);
    ASSERT_EQ(identity(process->client(), -1), -1);
    ASSERT_EQ(identity(process->client(), 0), 0);
    ASSERT_EQ(identity(process->client(), 0xfeedf00d), 0xfeedf00d);

    ASSERT_EQ(as_double(process->client(), 10), 10.0);
    ASSERT_EQ(as_double(process->client(), -10), -10.0);
    ASSERT_EQ(as_double(process->client(), 0), 0.0);

    ASSERT_EQ(muli(process->client(), 10, 10), 100);
    ASSERT_EQ(muli(process->client(), -10, 100), -1000);

    ASSERT_EQ(mulf(process->client(), 10.0, 10.0), 100.0);
    ASSERT_EQ(mulf(process->client(), -10.0, 100.0), -1000.0);

    ASSERT_EQ(print_int(process->client(), 1), "1");
    ASSERT_EQ(print_int(process->client(), -10), "-10");

    std::vector<int> vect_list;
    vect_list.push_back(0);
    vect_list.push_back(1);
    vect_list.push_back(2);
    ASSERT_EQ(print_list(process->client(), vect_list), "012");

    ASSERT_EQ(print_wide(process->client(), 1.1), L"1.1");
    ASSERT_EQ(print_wide(process->client(), -10.1), L"-10.1");

    ASSERT_EQ(sum3(process->client(), -10, 10, 0), 0);
    ASSERT_EQ(sum3(process->client(), 1, 1, 1), 3);

    ASSERT_EQ(sum4(process->client(), 10, -1, -10, 1), 0);
    ASSERT_EQ(sum4(process->client(), 1, 1, 1, 1), 4);

    ASSERT_EQ(sum5(process->client(), 10, -5, -1, 1, -5), 0);
    ASSERT_EQ(sum5(process->client(), 10, -5, -1, 1, 5), 10);

    std::vector<int> vect = list(process->client(), 0, 1, 2, 3);
    for(size_t i=0; i<vect.size(); i++)
        ASSERT_EQ(i, vect.at(i));

    endProcess(process->client()); // end_process

    // Get the process->client()
    sandboxed::TargetProcess *returning_process = 
            sandboxed::Broker::instance()->waitForTargets();
    ASSERT_TRUE(returning_process);
    delete returning_process;
}

TEST(Sandboxed_Broker, MoreProcess) {
    
    int i;
    LONG last = lRun;
    std::vector<sandboxed::TargetProcess *> processList;

    for (i = 0; i < MAXIMUM_WAIT_OBJECTS+10; i++) {
        sandboxed::TargetProcess *process = spawnTarget();
        ASSERT_TRUE(process);
        process->client()->waitForConnection();
        processList.push_back(process);
    }

	RPC::ClientCall<int()> one("one");
    RPC::ClientCall<bool()> endProcess("endProcess");

	while (processList.size() > 0){
        std::vector<sandboxed::TargetProcess *>::iterator it =
            processList.begin();

        ASSERT_EQ(one((*it)->client()), 1);
        ASSERT_EQ(endProcess((*it)->client()), true);

        sandboxed::TargetProcess *returning_process = 
            sandboxed::Broker::instance()->waitForTargets();
        ASSERT_EQ(*it, returning_process);
        delete returning_process;

        processList.erase(it);
    }
}

void doBroker(int argc, char *argv[]) {
    sandboxed::Broker::instance()->initialize();
    ::testing::InitGoogleMock(&argc, argv);
    RUN_ALL_TESTS();
    getchar();
}

class TargetUnit
{
public:
    void voidfunc() { ++lRun; }
    int one() { return 1; }
    bool True() { return true; }
    bool False() { return false; }
    double pi() { return 3.14; }
    int identity(int a) { return a; }
    double as_double(int a) { return a; }
    int muli(int a, int b) { return a * b; }
    double mulf(double a, double b) { return a * b; }
    std::string print_int(int a) {
        std::ostringstream ss;
        ss << a;
        return ss.str();
    }
    std::string print_list(std::vector<int> a) {
        std::ostringstream ss;
        std::vector<int>::iterator it;
        for(it = a.begin(); it != a.end(); it++)
            ss << *it;
        return ss.str();
    }
    std::wstring print_wide(double a) {
        std::ostringstream ss;
        ss << a;
        std::wstring retval;
        std::string result = ss.str();
        UTF8ToWide(result.c_str(), result.length(), &retval);
        return retval;
    }
    int sum3(int a, int b, int c) { return a + b + c; }
    int sum4(int a, int b, int c, int d) { return a + b + c + d; }
    int sum5(int a, int b, int c, int d, int e) { return a + b + c + d + e; }
    std::vector<int> list(int a, int b, int c, int d) { 
        std::vector<int> list;
        list.push_back(a);
        list.push_back(b);
        list.push_back(c);
        list.push_back(d);
        return list; 
    }
    bool endProcess() {
        sandboxed::Platform::instance()->wakeup();
        return true;
    }
};

void doTarget(int argc, char *argv[])
{
    ++lRun;

    //Sleep(20000);

    sandboxed::Target::instance()->initialize();
    sandboxed::Target::instance()->lowerToken();

    sandboxed::Target *target =
        sandboxed::Target::instance();
    target->client()->waitForConnection();

    TargetUnit unit;

    target->server()->registerCallback("voidfunc", new RPC::ServerCall<void()>(
        &unit, &TargetUnit::voidfunc));
    target->server()->registerCallback("one", new RPC::ServerCall<int()>(
        &unit, &TargetUnit::one));
    target->server()->registerCallback("True", new RPC::ServerCall<bool()>(
        &unit, &TargetUnit::True));
    target->server()->registerCallback("False", new RPC::ServerCall<bool()>(
        &unit, &TargetUnit::False));
    target->server()->registerCallback("pi", new RPC::ServerCall<double()>(
        &unit, &TargetUnit::pi));
    target->server()->registerCallback("identity", new RPC::ServerCall<int(int)>(
        &unit, &TargetUnit::identity));
    target->server()->registerCallback("as_double", new RPC::ServerCall<double(int)>(
        &unit, &TargetUnit::as_double));
    target->server()->registerCallback("muli", new RPC::ServerCall<int(int, int)>(
        &unit, &TargetUnit::muli));
    target->server()->registerCallback("mulf", new RPC::ServerCall<double(double, double)>(
        &unit, &TargetUnit::mulf));
    target->server()->registerCallback("print_int", new RPC::ServerCall<std::string(int)>(
        &unit, &TargetUnit::print_int));
    target->server()->registerCallback("print_list", new RPC::ServerCall<std::string(std::vector<int>)>(
        &unit, &TargetUnit::print_list));
    target->server()->registerCallback("print_wide", new RPC::ServerCall<std::wstring(double)>(
        &unit, &TargetUnit::print_wide));
    target->server()->registerCallback("sum3", new RPC::ServerCall<int(int,int,int)>(
        &unit, &TargetUnit::sum3));
    target->server()->registerCallback("sum4", new RPC::ServerCall<int(int,int,int,int)>(
        &unit, &TargetUnit::sum4));
    target->server()->registerCallback("sum5", new RPC::ServerCall<int(int,int,int,int,int)>(
        &unit, &TargetUnit::sum5));
    target->server()->registerCallback("list", new RPC::ServerCall<std::vector<int>(int, int, int, int)>(
        &unit, &TargetUnit::list));

    target->server()->registerCallback("endProcess", new RPC::ServerCall<bool()>(
        &unit, &TargetUnit::endProcess));

    sandboxed::Platform::instance()->waitForEvents();
    target->shutdown();
}

int main(int argc, char *argv[])
{
    sandboxed::Platform platform;
    if (sandboxed::Broker::instance())
        doBroker(argc, argv);
    else
        doTarget(argc, argv);
    return 0;
}

/* Modeline for vim: set tw=79 et ts=4: */
