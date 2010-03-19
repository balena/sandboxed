/** @file target.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 3/3/2010 15:00:53
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOXED_TARGET_H
#define SANDBOXED_TARGET_H

#include <sandboxed/common.h>
#include <sandboxed/rpc_client.h>
#include <sandboxed/rpc_server.h>

namespace sandboxed {

using sandbox::ResultCode;

class Target
{
public:
    static Target *instance();

    virtual ~Target() {}

    virtual ResultCode initialize()=0;
    virtual void lowerToken()=0;

    virtual RPC::Client *client() const=0;
    virtual RPC::Server *server() const=0;

    virtual void shutdown()=0;
};

} // namespace sandboxed

#endif // SANDBOXED_TARGET_H

/* Modeline for vim: set tw=79 et ts=4: */

