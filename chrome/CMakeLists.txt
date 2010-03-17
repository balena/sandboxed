# @file CMakeLists.txt
# @author Guilherme Versiani <guibv@comunip.com.br>
# @date 2/3/2010 12:10:07

# Copyright (c) 2010 ComunIP S/A. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

IF(WIN32)
  ADD_DEFINITIONS(-DNOMINMAX)
ENDIF(WIN32)

FIND_PACKAGE(GTest REQUIRED)

ADD_SUBDIRECTORY(base)
ADD_SUBDIRECTORY(chrome)
ADD_SUBDIRECTORY(sandbox)

# Modeline for vim: set tw=79 et ts=4:

