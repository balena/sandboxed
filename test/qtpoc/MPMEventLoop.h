// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MPMEVENTLOOP_H
#define MPMEVENTLOOP_H

#include <QObject>
#include <QTimer>
#include <QApplication>

#include <sandboxed/platform.h>
#include <sandboxed/broker.h>

class MPMEventLoop : public QObject {
    Q_OBJECT
public:
    MPMEventLoop() {
        QObject::connect(&mTimer, SIGNAL(timeout()), this, SLOT(processEvents()));
        mTimer.start(10);
    }
public slots:
    void processEvents() {
        sandboxed::Platform::instance()->peekEvents();
        if (sandboxed::Broker::instance()) {
            sandboxed::TargetProcess *target_process;
            if (sandboxed::Broker::instance()->peekTargets(&target_process))
                qApp->quit();
        }
    }

private:
    QTimer mTimer;
};

#endif // MPMEVENTLOOP_H

/* Modeline for vim: set tw=79 et ts=4: */

