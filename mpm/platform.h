/** @file platform.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 10/3/2010 12:53:09
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MPM_PLATFORM_H
#define MPM_PLATFORM_H

#include <base/at_exit.h>
#include <base/message_loop.h>

namespace mpm {

class Platform
{
public:
    Platform();
    virtual ~Platform();

    static Platform *instance();

    /** Process all pending events, but don't wait/sleep. Return as soon as
        all items that can be run are taken care of.
     */
    void peekEvents();

    /** Run the Multiprocess platform message loop.
     */
    void waitForEvents();

    /** Signals the waitForEvents() method to return after it is done
        processing all pending messages. This method may only be called
        on the same thread that called waitForEvents(), and waitForEvents()
        must still be on the call stack.
     */
    void wakeup();

private:
    base::AtExitManager *exit_manager_;
    MessageLoop *main_loop_;
};

} // namespace mpm

#endif // MPM_PLATFORM_H

/* Modeline for vim: set tw=79 et ts=4: */

