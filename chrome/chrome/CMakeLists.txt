# @file CMakeLists.txt
# @author Guilherme Versiani <guibv@comunip.com.br>
# @date 2/3/2010 10:49:52

# Copyright (c) 2010 ComunIP S/A. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

INCLUDE_DIRECTORIES(.. ${GTEST_INCLUDE_DIR})

ADD_LIBRARY(chrome STATIC
  common/chrome_counters.cc
  common/chrome_counters.h
  common/chrome_switches.cc
  common/chrome_switches.h
  common/ipc_channel.h
  common/ipc_channel_handle.h
  common/ipc_channel_proxy.cc
  common/ipc_channel_proxy.h
  common/ipc_channel_win.cc
  common/ipc_channel_win.h
  common/ipc_logging.cc
  common/ipc_logging.h
  common/ipc_maybe.h
  common/ipc_message.cc
  common/ipc_message.h
  common/ipc_message_macros.h
  common/ipc_message_utils.cc
  common/ipc_message_utils.h
  common/ipc_sync_channel.cc
  common/ipc_sync_channel.h
  common/ipc_sync_message.cc
  common/ipc_sync_message.h
  common/thumbnail_score.h
)

ADD_DEPENDENCIES(chrome chrome_base chrome_sandbox)
TARGET_LINK_LIBRARIES(chrome chrome_base chrome_sandbox ${GTEST_LIBRARIES})
SET_TARGET_PROPERTIES(chrome
  PROPERTIES
    RELEASE_OUTPUT_NAME chrome
    DEBUG_OUTPUT_NAME chromed
)

# Modeline for vim: set tw=79 et ts=4:
