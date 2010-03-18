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

class SANDBOXED_DLL Broker
{
public:
    /** Get the Broker instance.
     */
    static Broker* instance();

    virtual ~Broker() {}

    /** Spawn a copy of the current process with the passed in arguments.
     */
    virtual TargetProcess *spawnTarget(const wchar_t *arguments=L"")=0;

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

