/** @file target_process.cc
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 08/03/2010 23.06.34
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <sandboxed/target_process_internal.h>

namespace sandboxed {

TargetProcessImpl::TargetProcessImpl(HANDLE process)
    : mProcess(process),
      mThread("BrokerChannel")
{
    base::Thread::Options options;
    options.message_loop_type = MessageLoop::TYPE_IO;
    mThread.StartWithOptions(options);

    mClientRPC.reset(new RPC::ClientImpl);
    mServerRPC.reset(new RPC::ServerImpl);

    IPC::ChannelProxy::MessageFilter *filter =
        mClientRPC->createFilter();
    IPC::Channel::Listener *listener =
        mServerRPC->createListener();

    std::ostringstream ss;
    ss << GetProcessId(process);
    mChannelProxy.reset(new IPC::ChannelProxy(ss.str(), IPC::Channel::MODE_SERVER,
        listener, filter, mThread.message_loop()));

    mClientRPC->setChannelProxy(mChannelProxy.get());
    mServerRPC->setChannelProxy(mChannelProxy.get());
}

TargetProcessImpl::~TargetProcessImpl() {
    mChannelProxy.reset();
    mClientRPC.reset();
    mServerRPC.reset();
    mThread.Stop();
    ::CloseHandle(mProcess);
}

HANDLE TargetProcessImpl::getProcess() {
    return mProcess;
}

RPC::Client *TargetProcessImpl::client() const {
    return mClientRPC.get();
}

RPC::Server *TargetProcessImpl::server() const {
    return mServerRPC.get();
}

} // namespace sandboxed

/* Modeline for vim: set tw=79 et ts=4: */

