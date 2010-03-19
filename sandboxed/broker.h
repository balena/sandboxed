/** @file broker.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 1/3/2010 11:40:37
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOXED_BROKER_H
#define SANDBOXED_BROKER_H

#include <sandboxed/common.h>
#include <sandboxed/type_traits.h>
#include <sandboxed/target_process.h>

namespace sandboxed {

using sandbox::ResultCode;
using sandbox::TargetPolicy;

/** Broker class exposes all the broker API.
    The basic use is to start the target(s) and wait for them to end.

    This API is intended to be called in the following order (error checking
    omitted):
    Broker* broker = Broker::instance();
    broker->initialize();
    broker->spawnTarget(target_args, policy);
    // -- later you can call:
    broker->waitForTargets();
 */
class Broker
{
public:
    /** Get the Broker instance.
     */
    static Broker* instance();

    virtual ~Broker() {}

    /** Initializes the broker. Must be called before any other on this class.
        returns ALL_OK if successful. All other return values imply failure.
        If the return is ERROR_GENERIC, you can call ::GetLastError() to get
        more information.
     */
    virtual ResultCode initialize()=0;

    /** Returns the interface pointer to a new, empty policy object. Use this
        interface to specify the sandbox policy for new processes created by
        spawnTarget().
     */
    virtual TargetPolicy* createPolicy()=0;

    /** Spawn a copy of the current process with the passed in arguments.
     */
    virtual TargetProcess *spawnTarget(const wchar_t *arguments,
                                       TargetPolicy* policy)=0;

    /** This function will check if there are any closed target process to be
        returned, but don't wait. The return value indicates if the 'process'
        parameter should be inspected: if there are processes to be returned
        the 'process' parameter will be different from NULL; if not, it will be
        NULL.
     */
    virtual bool peekTargets(TargetProcess **process)=0;

    /** This function will wait for any of the pending targets to be closed. If
        you need to interrupt this call, you should call 'wakeup' method.
     */
    virtual TargetProcess *waitForTargets()=0;

    /** Interrupts the 'waitForTargets' function.
     */
    virtual void wakeup()=0;
};

} // namespace sandboxed

#endif // SANDBOXED_BROKER_H

/* Modeline for vim: set tw=79 et ts=4: */

