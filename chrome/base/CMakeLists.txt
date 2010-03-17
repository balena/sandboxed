# @file CMakeLists.txt
# @author Guilherme Versiani <guibv@comunip.com.br>
# @date 2/3/2010 10:49:52

# Copyright (c) 2010 ComunIP S/A. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

INCLUDE_DIRECTORIES(.. ${GTEST_INCLUDE_DIR})

SET(DMG_FP_SRCS
  third_party/dmg_fp/dmg_fp.h
  third_party/dmg_fp/dtoa.cc
  third_party/dmg_fp/g_fmt.cc
)

SOURCE_GROUP(dmg_fp FILES ${DMG_FP_SRCS})

SET(NSPR_SRCS
  third_party/nspr/prcpucfg.h
  third_party/nspr/prcpucfg_win.h
  third_party/nspr/prtime.cc
  third_party/nspr/prtime.h
  third_party/nspr/prtypes.h
)

SOURCE_GROUP(nspr FILES ${NSPR_SRCS})

ADD_LIBRARY(chrome_base STATIC
  ${DMG_FP_SRCS}
  ${NSPR_SRCS}
  atomic_ref_count.h
  atomicops.h
  atomicops_internals_x86_msvc.h
  at_exit.cc
  at_exit.h
  base_switches.cc
  base_switches.h
  basictypes.h
  command_line.cc
  command_line.h
  compiler_specific.h
  condition_variable.h
  condition_variable_win.cc
  cpu.cc
  cpu.h
  debug_util.h
  debug_util_win.cc
  dynamic_annotations.cc
  dynamic_annotations.h
  file_path.cc
  file_path.h
  float_util.h
  format_macros.h
  hash_tables.h
  histogram.cc
  histogram.h
  json_reader.cc
  json_reader.h
  json_writer.cc
  json_writer.h
  lazy_instance.cc
  lazy_instance.h
  lock.cc
  lock.h
  lock_impl.h
  lock_impl_win.cc
  logging.cc
  logging.h
  message_loop.cc
  message_loop.h
  message_pump.h
  message_pump_default.cc
  message_pump_default.h
  message_pump_win.cc
  message_pump_win.h
  non_thread_safe.cc
  non_thread_safe.h
  object_watcher.cc
  object_watcher.h
  observer_list.h
  observer_list_threadsafe.h
  pickle.cc
  pickle.h
  platform_thread.h
  platform_thread_win.cc
  port.h
  process.h
  process_win.cc
  process_util.h
  process_util_win.cc
  ref_counted.cc
  ref_counted.h
  registry.cc
  registry.h
  revocable_store.cc
  revocable_store.h
  scoped_handle.h
  scoped_handle_win.h
  scoped_nsautorelease_pool.h
  scoped_ptr.h
  shared_memory.h
  shared_memory_win.cc
  singleton.h
  singleton_objc.h
  stats_counters.h
  stats_table.cc
  stats_table.h
  string16.h
  string_escape.cc
  string_escape.h
  string_piece.h
  string_util.cc
  string_util.h
  string_util_win.cc
  string_util_win.h
  sys_info.h
  sys_info_win.cc
  sys_string_conversions.h
  sys_string_conversions_win.cc
  system_monitor.cc
  system_monitor.h
  system_monitor_win.cc
  task.h
  thread.cc
  thread.h
  thread_collision_warner.cc
  thread_collision_warner.h
  thread_local.h
  thread_local_win.cc
  thread_local_storage.h
  thread_local_storage_win.cc
  time.cc
  time.h
  time_win.cc
  timer.cc
  timer.h
  tracked.cc
  tracked.h
  tracked_objects.cc
  tracked_objects.h
  tuple.h
  values.cc
  values.h
  waitable_event.h
  waitable_event_win.cc
  waitable_event_watcher.h
  waitable_event_watcher_win.cc
  win_util.cc
  win_util.h
)
TARGET_LINK_LIBRARIES(chrome_base dbghelp.lib psapi.lib ${GTEST_LIBRARIES})
SET_TARGET_PROPERTIES(chrome_base
  PROPERTIES
    RELEASE_OUTPUT_NAME chromebase
    DEBUG_OUTPUT_NAME chromebased
)

# Modeline for vim: set tw=79 et ts=4:
