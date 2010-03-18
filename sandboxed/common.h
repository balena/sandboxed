/** @file common.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 3/3/2010 15:02:48
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOXED_BASE_H
#define SANDBOXED_BASE_H

#include <base/values.h>
#include <base/at_exit.h>
#include <base/command_line.h>
#include <base/message_loop.h>
#include <sandbox/src/sandbox.h>

// By default, we won't supply a DLL library (use at your own risk):
#ifdef _MSC_VER
#if defined(_DLL)
    #define SANDBOXED_DLL __declspec(dllexport)
#else
    #define SANDBOXED_DLL __declspec(dllimport)
#endif
#endif // _MSC_VER

// This is for those who wants to deploy simple static libraries:
#ifndef SANDBOXED_DLL
#define SANDBOXED_DLL
#endif

#endif // SANDBOXED_BASE_H

/* Modeline for vim: set tw=79 et ts=4: */

