/** @file target.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 3/3/2010 15:00:53
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MPM_TARGET_H
#define MPM_TARGET_H

#include <mpm/common.h>
#include <mpm/rpc_client.h>
#include <mpm/rpc_server.h>

namespace mpm {

class Target
{
public:
    static Target *instance();

    virtual ~Target() {}

    virtual RPC::Client *client() const=0;
    virtual RPC::Server *server() const=0;

    virtual void shutdown()=0;
};

} // namespace mpm

#endif // MPM_TARGET_H

/* Modeline for vim: set tw=79 et ts=4: */

