/** @file Window.cpp
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 3/3/2010 11:45:46
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "stdafx.h"
#include "Window.h"
#include <base/message_loop.h>

int Window::CreateAndLoop(const wchar_t *lpszTitle, int nCmdShow)
{
    MSG msg;
 
    // Create the main window
    if (CreateEx() == NULL)
        return 1; // Window creation failed
 
    SetWindowText(lpszTitle);

    // Show the window
    ShowWindow(nCmdShow);
    UpdateWindow();
 
    // Mixed message loop
    while (true) {    
        MessageLoop::current()->RunAllPending();
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
 
    return msg.wParam;
}

/* Modeline for vim: set tw=79 et ts=4: */

