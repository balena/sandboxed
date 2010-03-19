/** @file target_process.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 08/03/2010 23.04.46
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOXED_TARGETPROCESS_H
#define SANDBOXED_TARGETPROCESS_H

#include <sandboxed/common.h>
#include <sandboxed/rpc_client.h>
#include <sandboxed/rpc_server.h>

namespace sandboxed {

class TargetProcess
{
public:
    virtual ~TargetProcess() {}

    virtual RPC::Client *client() const=0;
    virtual RPC::Server *server() const=0;
};

} // namespace sandboxed

#endif // SANDBOXED_TARGETPROCESS_H

/* Modeline for vim: set tw=79 et ts=4: */

