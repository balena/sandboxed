// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifdef _HAS_TR1
#undef _HAS_TR1
#define _HAS_TR1 1
#endif

#include "MPMEventLoop.h"

#include <QApplication>
#include <QAction>
#include <QtWebKit>

#include <sandboxed/platform.h>
#include <sandboxed/broker.h>
#include <sandboxed/target.h>
#include <base/win_util.h>

namespace {

// The DLLs listed here are known (or under strong suspicion) of causing crashes
// when they are loaded in the renderer.
const wchar_t* const kTroublesomeDlls[] = {
  L"adialhk.dll",                 // Kaspersky Internet Security.
  L"acpiz.dll",                   // Unknown.
  L"avgrsstx.dll",                // AVG 8.
  L"btkeyind.dll",                // Widcomm Bluetooth.
  L"cmcsyshk.dll",                // CMC Internet Security.
  L"dockshellhook.dll",           // Stardock Objectdock.
  L"GoogleDesktopNetwork3.DLL",   // Google Desktop Search v5.
  L"fwhook.dll",                  // PC Tools Firewall Plus.
  L"hookprocesscreation.dll",     // Blumentals Program protector.
  L"hookterminateapis.dll",       // Blumentals and Cyberprinter.
  L"hookprintapis.dll",           // Cyberprinter.
  L"imon.dll",                    // NOD32 Antivirus.
  L"ioloHL.dll",                  // Iolo (System Mechanic).
  L"kloehk.dll",                  // Kaspersky Internet Security.
  L"lawenforcer.dll",             // Spyware-Browser AntiSpyware (Spybro).
  L"libdivx.dll",                 // DivX.
  L"lvprcinj01.dll",              // Logitech QuickCam.
  L"madchook.dll",                // Madshi (generic hooking library).
  L"mdnsnsp.dll",                 // Bonjour.
  L"moonsysh.dll",                // Moon Secure Antivirus.
  L"npdivx32.dll",                // DivX.
  L"npggNT.des",                  // GameGuard 2008.
  L"npggNT.dll",                  // GameGuard (older).
  L"oawatch.dll",                 // Online Armor.
  L"pavhook.dll",                 // Panda Internet Security.
  L"pavshook.dll",                // Panda Antivirus.
  L"pctavhook.dll",               // PC Tools Antivirus.
  L"prntrack.dll",                // Pharos Systems.
  L"radhslib.dll",                // Radiant Naomi Internet Filter.
  L"radprlib.dll",                // Radiant Naomi Internet Filter.
  L"rlhook.dll",                  // Trustware Bufferzone.
  L"r3hook.dll",                  // Kaspersky Internet Security.
  L"sahook.dll",                  // McAfee Site Advisor.
  L"sbrige.dll",                  // Unknown.
  L"sc2hook.dll",                 // Supercopier 2.
  L"sguard.dll",                  // Iolo (System Guard).
  L"smum32.dll",                  // Spyware Doctor version 6.
  L"smumhook.dll",                // Spyware Doctor version 5.
  L"ssldivx.dll",                 // DivX.
  L"syncor11.dll",                // SynthCore Midi interface.
  L"systools.dll",                // Panda Antivirus.
  L"tfwah.dll",                   // Threatfire (PC tools).
  L"wblind.dll",                  // Stardock Object desktop.
  L"wbhelp.dll",                  // Stardock Object desktop.
  L"winstylerthemehelper.dll"     // Tuneup utilities 2006.
};

// Adds policy rules for unloaded the known dlls that cause chrome to crash.
// Eviction of injected DLLs is done by the sandbox so that the injected module
// does not get a chance to execute any code.
void AddDllEvictionPolicy(sandboxed::TargetPolicy* policy) {
  for (int ix = 0; ix != arraysize(kTroublesomeDlls); ++ix) {
    // To minimize the list we only add an unload policy if the dll is also
    // loaded in this process. All the injected dlls of interest do this.
    if (::GetModuleHandleW(kTroublesomeDlls[ix])) {
      LOG(WARNING) << "dll to unload found: " << kTroublesomeDlls[ix];
      policy->AddDllToUnload(kTroublesomeDlls[ix]);
    }
  }
}

} // empty namespace

sandboxed::TargetPolicy* createDefaultPolicy() {
    sandboxed::TargetPolicy *policy =
        sandboxed::Broker::instance()->createPolicy();

    policy->SetJobLevel(sandbox::JOB_LIMITED_USER, JOB_OBJECT_UILIMIT_ALL);

    sandbox::TokenLevel initial_token = sandbox::USER_UNPROTECTED;
    if (win_util::GetWinVersion() > win_util::WINVERSION_XP) {
        // On 2003/Vista the initial token has to be restricted if the main
        // token is restricted.
        initial_token = sandbox::USER_RESTRICTED_SAME_ACCESS;
    }

    policy->SetTokenLevel(initial_token, initial_token);
    policy->SetDelayedIntegrityLevel(sandbox::INTEGRITY_LEVEL_LOW);
    AddDllEvictionPolicy(policy);

    return policy;
}

sandboxed::TargetProcess *spawnTarget() {
    sandboxed::TargetPolicy *policy = createDefaultPolicy();
    sandboxed::TargetProcess *process =
        sandboxed::Broker::instance()->spawnTarget(L"", policy);
    policy->Release();
    return process;
}

void doBroker(int argc, char *argv[]) {
    sandboxed::Broker::instance()->initialize();

    // Create application
    QApplication::setGraphicsSystem( "raster" );
    QApplication app( argc, argv );

    MPMEventLoop loop;

    sandboxed::TargetProcess *process = spawnTarget();
    process->client()->waitForConnection();

    app.exec();
}

void doTarget(int argc, char *argv[]) {
    // Create application
    QApplication::setGraphicsSystem( "raster" );
    QApplication app( argc, argv );

    QWebView webView;

    QAction *copyAction = webView.pageAction(QWebPage::Copy);
	copyAction->setShortcut(QKeySequence::Copy);
    webView.addAction(copyAction);

    webView.load(QUrl("http://www.google.com"));
    webView.show();

    MPMEventLoop loop;
    app.exec();
}

int main(int argc, char **argv) {
    sandboxed::Platform platform;
    if (sandboxed::Broker::instance())
        doBroker(argc, argv);
    else {
        sandboxed::Target *target =
            sandboxed::Target::instance();

        target->initialize();
        target->client()->waitForConnection();
        target->lowerToken();

        doTarget(argc, argv);

        target->shutdown();
    }

    return 0;
}
