/** @file rpc_server.cc
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 16/3/2010 15:47:43
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <mpm/rpc_server_internal.h>
#include <chrome/common/ipc_message_utils.h>

namespace RPC {

ServerImpl::ServerImpl()
    : mChannelProxy(NULL)
{

}

ServerImpl::~ServerImpl() {
    ListenerMap::iterator it;
    for (it = mListeners.begin(); it != mListeners.end(); ++it)
        delete (*it++).second;
}

IPC::Channel::Listener *ServerImpl::createListener() {
    return new MessageListener(this);
}

void ServerImpl::setChannelProxy(IPC::ChannelProxy *channelProxy) {
    mChannelProxy = channelProxy;
}

bool ServerImpl::registerCallback(const std::string &fname, Listener *listener) {
    mListeners.insert(std::make_pair(fname, listener));
    return true;
}

void ServerImpl::dispatchMessage(const IPC::Message& message) {
    ListenerMap::iterator it;

    void *itor = 0;
    std::string fname;
    ListValue params;

    ReadParam(&message, &itor, &fname);
    ReadParam(&message, &itor, &params);

    it = mListeners.find(fname);
    if (it != mListeners.end()) {
        Value *retval = (*it).second->invoke(params);
        if (retval && retval->GetType() != Value::TYPE_NULL) {
            ListValue ret;
            ret.Append(retval);
            IPC::Message *msg =
                new IPC::Message(message.routing_id(),
                    message.type(), IPC::Message::PRIORITY_NORMAL);
            msg->set_reply();
            WriteParam(msg, ret);
            mChannelProxy->Send(msg);
        }
        else if (retval)
            delete retval;
    }
    else {
        // TODO: errors
    }
}

void ServerImpl::MessageListener::OnMessageReceived(const IPC::Message& message) {
    outer_->dispatchMessage(message);
}

void ServerImpl::MessageListener::OnChannelError() {
    //DCHECK(false) << "Broker gone away";
}

void ServerImpl::MessageListener::OnChannelConnected(int32 peer_pid) {
    //DCHECK(false) << "Spurious process connected : " << peer_pid;
}

} // namespace RPC

/* Modeline for vim: set tw=79 et ts=4: */

