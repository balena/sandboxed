/** @file target_process_internal.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 9/3/2010 21:52:29
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MPM_TARGET_PROCESS_INTERNAL_H
#define MPM_TARGET_PROCESS_INTERNAL_H

#include <mpm/target_process.h>
#include <mpm/rpc_client_internal.h>
#include <mpm/rpc_server_internal.h>
#include <base/thread.h>
#include <base/scoped_ptr.h>

namespace mpm {

class TargetProcessImpl : public TargetProcess
{
public:
    TargetProcessImpl(HANDLE process);
    virtual ~TargetProcessImpl();

    HANDLE getProcess();
    virtual RPC::Client *client() const;
    virtual RPC::Server *server() const;

protected:
    HANDLE mProcess;

    base::Thread                  mThread;
    scoped_ptr<IPC::ChannelProxy> mChannelProxy;
    scoped_ptr<RPC::ClientImpl>   mClientRPC;
    scoped_ptr<RPC::ServerImpl>   mServerRPC;
};

} // namespace mpm

#endif // MPM_TARGET_PROCESS_INTERNAL_H

/* Modeline for vim: set tw=79 et ts=4: */

