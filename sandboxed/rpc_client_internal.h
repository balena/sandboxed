/** @file rpc_client_internal.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 16/3/2010 14:36:54
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOXED_RPC_CLIENT_INTERNAL_H
#define SANDBOXED_RPC_CLIENT_INTERNAL_H

#include <sandboxed/rpc_client.h>
#include <base/lock.h>
#include <base/condition_variable.h>
#include <base/atomicops.h>
#include <chrome/common/ipc_channel_proxy.h>
#include <list>

namespace RPC {

class ClientImpl
    : public Client
{
public:
    ClientImpl();
    virtual ~ClientImpl();

    void setChannelProxy(IPC::ChannelProxy *channelProxy);
    IPC::ChannelProxy::MessageFilter *createFilter();
    virtual bool sendMessage(IPC::Message *message);
    virtual IPC::Message *getMessage();
    virtual void waitForConnection();

private:
    class MessageFilter : public IPC::ChannelProxy::MessageFilter {
    public:
        MessageFilter(ClientImpl *outer) : outer_(outer) {}
        virtual bool OnMessageReceived(const IPC::Message& message);
        virtual void OnChannelConnected(int32 peer_pid);
        virtual void OnChannelError();
    private:
        ClientImpl *outer_;
    };

    struct MessageSlot {
        MessageSlot(int32 id, IPC::Message *msg=NULL)
            : request_id(id), message(msg) {}
        int32 request_id;
        IPC::Message *message;
    };

    IPC::ChannelProxy      *mChannelProxy;
    Lock                    mLock;
    ConditionVariable       mCondVar;
    std::list<MessageSlot>  mIncomingMessages;
    base::subtle::Atomic32  mAtomicGenerator;
    bool                    mError;

    int32 newId();
};

} // namespace RPC

#endif // SANDBOXED_RPC_CLIENT_INTERNAL_H

/* Modeline for vim: set tw=79 et ts=4: */

