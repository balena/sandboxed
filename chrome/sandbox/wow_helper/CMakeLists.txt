# @file CMakeLists.txt
# @author Guilherme Versiani <guibv@comunip.com.br>
# @date 25/3/2010 12:10:37

# Copyright (c) 2010 ComunIP S/A. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

#
# Wow_helper.exe is a simple Win32 64-bit executable designed to help to
# sandbox a 32 bit application running on a 64 bit OS.
#

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
MARK_AS_ADVANCED(FORCE CMAKE_BACKWARDS_COMPATIBILITY)

PROJECT(wow_helper)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Debug")
ENDIF(NOT CMAKE_BUILD_TYPE)

# Set CMake modules path
SET(CMAKE_MODULE_PATH "../../../cmake/modules")

# Setup msvc
IF(MSVC)

  IF(MSVC60 OR MSVC70 OR MSVC71)

    SET(CMAKE_C_FLAGS "/W3")
    SET(CMAKE_C_FLAGS_DEBUG "/MTd /Zi /Gm /GX /Od /GZ")
    SET(CMAKE_C_FLAGS_RELEASE "/MT /GX /O2")
    SET(CMAKE_C_FLAGS_MINSIZEREL "/MT /GX /O1")
    SET(CMAKE_C_FLAGS_RELWITHDEBINFO "/MT /Zi /GX /O2")

    SET(CMAKE_CXX_FLAGS "/W3")
    SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Zi /Gm /GX /Od /GZ")
    SET(CMAKE_CXX_FLAGS_RELEASE "/MT /GX /O2")
    SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /GX /O1")
    SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT /Zi /GX /O2")

  ELSE(MSVC60 OR MSVC70 OR MSVC71)

    SET(CMAKE_C_FLAGS "/W3")
    SET(CMAKE_C_FLAGS_DEBUG "/MTd /Zi /Gm /EHsc /Od /RTC1")
    SET(CMAKE_C_FLAGS_RELEASE "/MT /EHsc /O2")
    SET(CMAKE_C_FLAGS_MINSIZEREL "/MT /EHsc /O1")
    SET(CMAKE_C_FLAGS_RELWITHDEBINFO "/MT /Zi /EHsc /O2")

    SET(CMAKE_CXX_FLAGS "/W3")
    SET(CMAKE_CXX_FLAGS_DEBUG "/MTd /Zi /Gm /EHsc /Od /RTC1")
    SET(CMAKE_CXX_FLAGS_RELEASE "/MT /EHsc /O2")
    SET(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /EHsc /O1")
    SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT /Zi /EHsc /O2")

  ENDIF(MSVC60 OR MSVC70 OR MSVC71)

ENDIF(MSVC)

IF(WIN32)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS=1 -DUNICODE -D_UNICODE -DOS_WIN=1)
  ADD_DEFINITIONS(-D_CRT_RAND_S -DCERT_CHAIN_PARA_HAS_EXTRA_FIELDS)
  ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN -D_SECURE_ATL -D_HAS_TR1=0)
  ADD_DEFINITIONS(-D__STDC_FORMAT_MACROS -DCHROMIUM_BUILD)
  ADD_DEFINITIONS(-DU_STATIC_IMPLEMENTATION -DNOMINMAX)
ENDIF(WIN32)

INCLUDE_DIRECTORIES(../..)

SET(WOW_HELPER_BASE_SRCS
  ../../base/scoped_ptr.h
)

SOURCE_GROUP(base FILES ${WOW_HELPER_BASE_SRCS})

SET(WOW_HELPER_SANDBOX_SRCS
  ../src/nt_internals.h
  ../src/resolver.h
)

SOURCE_GROUP(sandbox FILES ${WOW_HELPER_SANDBOX_SRCS})

SET(WOW_HELPER_SRCS
  service64_resolver.cc
  service64_resolver.h
  target_code.cc
  target_code.h
  wow_helper.cc
)

SOURCE_GROUP(wow_helper FILES ${WOW_HELPER_SRCS})

ADD_EXECUTABLE(wow_helper WIN32
  ${WOW_HELPER_BASE_SRCS}
  ${WOW_HELPER_SANDBOX_SRCS}
  ${WOW_HELPER_SRCS}
)

# Modeline for vim: set tw=79 et ts=4:

