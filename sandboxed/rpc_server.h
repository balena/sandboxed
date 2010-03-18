/** @file rpc_server.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 12/3/2010 18:21:45
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOXED_RPC_SERVER_H
#define SANDBOXED_RPC_SERVER_H

#include <sandboxed/common.h>

namespace RPC {

class Server {
public:
    class Listener {
    public:
        virtual Value *invoke(const ListValue &params)=0;
    };

    virtual ~Server() {}

    virtual bool registerCallback(const std::string &fname,
        Listener *listener)=0;
};

} // namespace RPC

#include <sandboxed/rpc_server_call.h>

#endif // SANDBOXED_RPC_SERVER_H

/* Modeline for vim: set tw=79 et ts=4: */

