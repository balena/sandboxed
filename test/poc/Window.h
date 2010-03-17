/** @file Window.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 3/3/2010 11:35:33
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_WINDOW_H
#define SANDBOX_WINDOW_H

#include "resource.h"

class Window : public CFrameWindowImpl<Window>
{
public:
    DECLARE_FRAME_WND_CLASS(_T("Simple WTL window"), IDR_MAINFRAME);

    int CreateAndLoop(const wchar_t *lpszTitle, int nCmdShow);
 
    BEGIN_MSG_MAP(CMyWindow)
        CHAIN_MSG_MAP(CFrameWindowImpl<Window>)
    END_MSG_MAP()
};

#endif // SANDBOX_WINDOW_H

/* Modeline for vim: set tw=79 et ts=4: */

