# @file CMakeLists.txt
# @author Guilherme Versiani <guibv@comunip.com.br>
# @date Tue Mar 09 21:43:13 BRT 2010

# Copyright (c) 2010 ComunIP S/A. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

INCLUDE_DIRECTORIES(.. ../chrome ${GTEST_INCLUDE_DIR})

ADD_DEFINITIONS(-DNOMINMAX)

ADD_LIBRARY(mpm STATIC
  broker.cc
  broker.h
  common.h
  platform.cc
  platform.h
  rpc_client.cc
  rpc_client.h
  rpc_client_call.h
  rpc_client_internal.h
  rpc_server.cc
  rpc_server.h
  rpc_server_call.h
  rpc_server_internal.h
  target.cc
  target.h
  target_process.cc
  target_process.h
  target_process_internal.h
  type_traits.h
  value_traits.h
)
TARGET_LINK_LIBRARIES(mpm chrome)
SET_TARGET_PROPERTIES(mpm
  PROPERTIES
    RELEASE_OUTPUT_NAME mpm
    DEBUG_OUTPUT_NAME mpmd
)

# Modeline for vim: set tw=79 et ts=4:
