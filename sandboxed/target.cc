/** @file target.cc
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 3/3/2010 15:04:55
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <sandboxed/target.h>
#include <sandboxed/rpc_client_internal.h>
#include <sandboxed/rpc_server_internal.h>
#include <chrome/common/ipc_message.h>
#include <chrome/common/ipc_channel_proxy.h>
#include <chrome/common/ipc_message_utils.h>
#include <base/time.h>
#include <base/scoped_ptr.h>
#include <base/thread.h>
#include <base/waitable_event.h>
#include <base/condition_variable.h>
#include <sandbox/src/sandbox_factory.h>
#include <sandbox/src/win_utils.h>

#include <map>

namespace sandboxed {

extern sandbox::TargetServices* g_target_service;

class TargetImpl : public Target,
                   public sandbox::SingletonBase<TargetImpl>
{
public:
    TargetImpl();
    virtual ~TargetImpl();

    virtual ResultCode initialize();
    virtual void lowerToken();

    virtual RPC::Client *client() const;
    virtual RPC::Server *server() const;

    virtual void shutdown();

private:
    sandbox::TargetServices      *mTargetServices;
    base::Thread                  mThread;
    scoped_ptr<IPC::ChannelProxy> mChannelProxy;
    scoped_ptr<RPC::ClientImpl>   mClientRPC;
    scoped_ptr<RPC::ServerImpl>   mServerRPC;
};

bool isBroker();

Target *Target::instance() {
    if (isBroker())
        return 0;
    return TargetImpl::GetInstance();
}

TargetImpl::TargetImpl()
    : mThread("TargetChannel")
{
    mTargetServices = sandbox::SandboxFactory::GetTargetServices();
}

TargetImpl::~TargetImpl() {

}

ResultCode TargetImpl::initialize() {
    ResultCode result = mTargetServices->Init();

    if (result == 0) {
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
        ss << ::GetCurrentProcessId();
        mChannelProxy.reset(new IPC::ChannelProxy(ss.str(), IPC::Channel::MODE_CLIENT,
            listener, filter, mThread.message_loop()));

        mClientRPC->setChannelProxy(mChannelProxy.get());
        mServerRPC->setChannelProxy(mChannelProxy.get());
    }

    return result;
}

void TargetImpl::lowerToken() {
    mTargetServices->LowerToken();
}

RPC::Client *TargetImpl::client() const {
    return mClientRPC.get();
}

RPC::Server *TargetImpl::server() const {
    return mServerRPC.get();
}

void TargetImpl::shutdown() {
    mChannelProxy.reset();
    mClientRPC.reset();
    mServerRPC.reset();
    mThread.Stop();
}

} // namespace sandboxed

/* Modeline for vim: set tw=79 et ts=4: */

