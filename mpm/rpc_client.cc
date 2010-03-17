/** @file rpc_client.cc
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 16/3/2010 14:42:39
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <mpm/rpc_client_internal.h>

namespace RPC {

ClientImpl::ClientImpl()
    : mCondVar(&mLock),
      mChannelProxy(NULL),
      mAtomicGenerator(0),
      mError(false)
{

}

ClientImpl::~ClientImpl() {

}

void ClientImpl::setChannelProxy(IPC::ChannelProxy *channelProxy) {
    mChannelProxy = channelProxy;
}

IPC::ChannelProxy::MessageFilter *ClientImpl::createFilter() {
    return new MessageFilter(this);
}

int32 ClientImpl::newId() {
    return base::subtle::NoBarrier_AtomicIncrement(&mAtomicGenerator, 1);
}

bool ClientImpl::sendMessage(IPC::Message *message) {
    int32 request_id = newId();
    mIncomingMessages.push_back(MessageSlot(request_id));
    message->set_routing_id(request_id);
    return mChannelProxy->Send(message);
}

IPC::Message *ClientImpl::getMessage() {
    if (mIncomingMessages.empty()) {
        DCHECK(false) << "You must send a message first!";
        return 0;
    }

    AutoLock guard(mLock);
    while (!mIncomingMessages.front().message && !mError)
        mCondVar.Wait();

    if (mError) {
        DCHECK(false) << "Channel error";
        return 0;
    }

    IPC::Message *incoming_message =
        mIncomingMessages.front().message;
    mIncomingMessages.pop_front();
    return incoming_message;
}

bool ClientImpl::MessageFilter::OnMessageReceived(const IPC::Message& message) {
    if (!message.is_reply())
        return false;

    AutoLock guard(outer_->mLock);
    std::list<MessageSlot>::iterator it;
    for (it = outer_->mIncomingMessages.begin(); it != outer_->mIncomingMessages.end(); ++it) {
        if ((*it).request_id == message.routing_id()) {
            (*it).message = new IPC::Message(message);
            outer_->mCondVar.Signal();
            return true;
        }
    }
    
    return false;
}

void ClientImpl::waitForConnection() {
    AutoLock guard(mLock);
    while (mIncomingMessages.empty() && !mError)
        mCondVar.Wait();

    if (mError) { // subtle remote error
        DCHECK(false) << "Channel error";
        return;
    }

    IPC::Message *incoming_message =
        mIncomingMessages.front().message;
    mIncomingMessages.pop_front();

    DCHECK(incoming_message == 0) << "Internal Error";
}

void ClientImpl::MessageFilter::OnChannelConnected(int32 peer_pid) {
    AutoLock guard(outer_->mLock);
    outer_->mIncomingMessages.push_back(MessageSlot(-1));
    outer_->mCondVar.Signal();
}

void ClientImpl::MessageFilter::OnChannelError() {
    AutoLock guard(outer_->mLock);
    outer_->mError = true;
    outer_->mCondVar.Signal();
}

} // namespace RPC

/* Modeline for vim: set tw=79 et ts=4: */

