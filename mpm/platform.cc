/** @file platform.cc
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 10/3/2010 12:52:06
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <mpm/platform.h>
#include <base/command_line.h>
#include <base/logging.h>
#include <base/win_util.h>
#include <base/process_util.h>
#include <sandbox/src/sandbox_factory.h>
#include <sandbox/src/dep.h>

namespace mpm {

static Platform* g_top_platform = NULL;

Platform::Platform() {
    g_top_platform = this;

    base::EnableTerminationOnHeapCorruption();

    // The exit manager is in charge of calling the dtors of singletons.
    exit_manager_ = new base::AtExitManager;

    win_util::WinVersion win_version = win_util::GetWinVersion();
    if (win_version < win_util::WINVERSION_VISTA) {
        // On Vista, this is unnecessary since it is controlled through the
        // /NXCOMPAT linker flag.
        // Enforces strong DEP support.
        sandbox::SetCurrentProcessDEP(sandbox::DEP_ENABLED);
    }

    // Get the interface pointer to the BrokerServices or TargetServices,
    // depending who we are.
    sandbox::BrokerServices* broker_service =
        sandbox::SandboxFactory::GetBrokerServices();
    if (!broker_service) {
        sandbox::TargetServices* target_service =
            sandbox::SandboxFactory::GetTargetServices();
    }

    CommandLine::Init(0, NULL);

    main_loop_ = new MessageLoop(MessageLoop::TYPE_IO);

    logging::InitLogging(NULL, logging::LOG_ONLY_TO_SYSTEM_DEBUG_LOG,
        logging::DONT_LOCK_LOG_FILE, logging::DELETE_OLD_LOG_FILE);
}

Platform::~Platform() {
    delete main_loop_;
    delete exit_manager_;

    g_top_platform = NULL;
}

Platform *Platform::instance() {
    return g_top_platform;
}

void Platform::peekEvents() {
    main_loop_->RunAllPending();
}

void Platform::waitForEvents() {
    main_loop_->Run();
}

void Platform::wakeup() {
    main_loop_->Quit();
}

} // namespace mpm

/* Modeline for vim: set tw=79 et ts=4: */

