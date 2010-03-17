/** @file rpc_server_internal.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 16/3/2010 15:43:42
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MPM_RPC_SERVER_INTERNAL_H
#define MPM_RPC_SERVER_INTERNAL_H

#include <mpm/common.h>
#include <mpm/rpc_server.h>
#include <chrome/common/ipc_channel_proxy.h>

namespace RPC {

class ServerImpl
    : public Server
{
public:
    class MessageListener : public IPC::Channel::Listener {
    public:
        MessageListener(ServerImpl *outer) : outer_(outer) {}
        virtual void OnMessageReceived(const IPC::Message& message);
        virtual void OnChannelConnected(int32 peer_pid);
        virtual void OnChannelError();
    private:
        ServerImpl *outer_;
    };

    ServerImpl();
    virtual ~ServerImpl();

    IPC::Channel::Listener *createListener();
    void setChannelProxy(IPC::ChannelProxy *channelProxy);
    virtual bool registerCallback(const std::string &fname,
        Listener *listener);

private:
    typedef std::map<std::string, RPC::Server::Listener *> ListenerMap;

    ListenerMap                 mListeners;
    IPC::ChannelProxy          *mChannelProxy;

    void dispatchMessage(const IPC::Message& message);
};

} // namespace RPC

#endif // MPM_RPC_SERVER_INTERNAL_H

/* Modeline for vim: set tw=79 et ts=4: */

