/** @file rpc_client.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 12/3/2010 18:14:09
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MPM_RPC_CLIENT_H
#define MPM_RPC_CLIENT_H

#include <chrome/common/ipc_message.h>

namespace RPC {

class Client
{
public:
    virtual ~Client() {}

    virtual bool sendMessage(IPC::Message *message)=0;
    virtual IPC::Message *getMessage()=0;
    virtual void waitForConnection()=0;
};

} // namespace RPC

#include <mpm/rpc_client_call.h>

#endif // MPM_RPC_CLIENT_H

/* Modeline for vim: set tw=79 et ts=4: */

