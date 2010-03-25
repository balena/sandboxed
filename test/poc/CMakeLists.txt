# @file CMakeLists.txt
# @author Guilherme Versiani <guibv@comunip.com.br>
# @date 2/3/2010 11:48:49

# Copyright (c) 2010 ComunIP S/A. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

FIND_PACKAGE(GTest REQUIRED)

INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/chrome
  ${GTEST_INCLUDE_DIR}
)

ADD_EXECUTABLE(poc WIN32
  Main.cpp
  stdafx.h
  Window.h
  Window.cpp
  resource.h
  poc.rc
)

ADD_DEPENDENCIES(poc chrome)
TARGET_LINK_LIBRARIES(poc chrome ${GTEST_LIBRARIES})

# Modeline for vim: set tw=79 et ts=4:
