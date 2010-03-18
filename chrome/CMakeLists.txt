# @file CMakeLists.txt
# @author Guilherme Versiani <guibv@comunip.com.br>
# @date 2/3/2010 12:10:07

# Copyright (c) 2010 ComunIP S/A. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

FIND_PACKAGE(GTest REQUIRED)

INCLUDE_DIRECTORIES(. ${GTEST_INCLUDE_DIR})

#
# Google Chrome base files:
#

SET(DMG_FP_SRCS
  base/third_party/dmg_fp/dmg_fp.h
  base/third_party/dmg_fp/dtoa.cc
  base/third_party/dmg_fp/g_fmt.cc
)

SOURCE_GROUP(base\\dmg_fp FILES ${DMG_FP_SRCS})

SET(NSPR_SRCS
  base/third_party/nspr/prcpucfg.h
  base/third_party/nspr/prcpucfg_win.h
  base/third_party/nspr/prtime.cc
  base/third_party/nspr/prtime.h
  base/third_party/nspr/prtypes.h
)

SOURCE_GROUP(base\\nspr FILES ${NSPR_SRCS})

SET(BASE_SRCS
  base/atomic_ref_count.h
  base/atomicops.h
  base/atomicops_internals_x86_msvc.h
  base/at_exit.cc
  base/at_exit.h
  base/base_switches.cc
  base/base_switches.h
  base/basictypes.h
  base/command_line.cc
  base/command_line.h
  base/compiler_specific.h
  base/condition_variable.h
  base/condition_variable_win.cc
  base/cpu.cc
  base/cpu.h
  base/debug_util.h
  base/debug_util_win.cc
  base/dynamic_annotations.cc
  base/dynamic_annotations.h
  base/file_path.cc
  base/file_path.h
  base/float_util.h
  base/format_macros.h
  base/hash_tables.h
  base/histogram.cc
  base/histogram.h
  base/json_reader.cc
  base/json_reader.h
  base/json_writer.cc
  base/json_writer.h
  base/lazy_instance.cc
  base/lazy_instance.h
  base/lock.cc
  base/lock.h
  base/lock_impl.h
  base/lock_impl_win.cc
  base/logging.cc
  base/logging.h
  base/message_loop.cc
  base/message_loop.h
  base/message_pump.h
  base/message_pump_default.cc
  base/message_pump_default.h
  base/message_pump_win.cc
  base/message_pump_win.h
  base/non_thread_safe.cc
  base/non_thread_safe.h
  base/object_watcher.cc
  base/object_watcher.h
  base/observer_list.h
  base/observer_list_threadsafe.h
  base/pickle.cc
  base/pickle.h
  base/platform_thread.h
  base/platform_thread_win.cc
  base/port.h
  base/process.h
  base/process_win.cc
  base/process_util.h
  base/process_util_win.cc
  base/ref_counted.cc
  base/ref_counted.h
  base/registry.cc
  base/registry.h
  base/revocable_store.cc
  base/revocable_store.h
  base/scoped_handle.h
  base/scoped_handle_win.h
  base/scoped_nsautorelease_pool.h
  base/scoped_ptr.h
  base/shared_memory.h
  base/shared_memory_win.cc
  base/singleton.h
  base/singleton_objc.h
  base/stats_counters.h
  base/stats_table.cc
  base/stats_table.h
  base/string16.h
  base/string_escape.cc
  base/string_escape.h
  base/string_piece.h
  base/string_util.cc
  base/string_util.h
  base/string_util_win.cc
  base/string_util_win.h
  base/sys_info.h
  base/sys_info_win.cc
  base/sys_string_conversions.h
  base/sys_string_conversions_win.cc
  base/system_monitor.cc
  base/system_monitor.h
  base/system_monitor_win.cc
  base/task.h
  base/thread.cc
  base/thread.h
  base/thread_collision_warner.cc
  base/thread_collision_warner.h
  base/thread_local.h
  base/thread_local_win.cc
  base/thread_local_storage.h
  base/thread_local_storage_win.cc
  base/time.cc
  base/time.h
  base/time_win.cc
  base/timer.cc
  base/timer.h
  base/tracked.cc
  base/tracked.h
  base/tracked_objects.cc
  base/tracked_objects.h
  base/tuple.h
  base/values.cc
  base/values.h
  base/waitable_event.h
  base/waitable_event_win.cc
  base/waitable_event_watcher.h
  base/waitable_event_watcher_win.cc
  base/win_util.cc
  base/win_util.h
)

SOURCE_GROUP(base FILES ${BASE_SRCS})

#
# Google Chrome chrome/common files:
#

SET(CHROME_COMMON_SRCS
  chrome/common/chrome_counters.cc
  chrome/common/chrome_counters.h
  chrome/common/chrome_switches.cc
  chrome/common/chrome_switches.h
  chrome/common/ipc_channel.h
  chrome/common/ipc_channel_handle.h
  chrome/common/ipc_channel_proxy.cc
  chrome/common/ipc_channel_proxy.h
  chrome/common/ipc_channel_win.cc
  chrome/common/ipc_channel_win.h
  chrome/common/ipc_logging.cc
  chrome/common/ipc_logging.h
  chrome/common/ipc_maybe.h
  chrome/common/ipc_message.cc
  chrome/common/ipc_message.h
  chrome/common/ipc_message_macros.h
  chrome/common/ipc_message_utils.cc
  chrome/common/ipc_message_utils.h
  chrome/common/ipc_sync_channel.cc
  chrome/common/ipc_sync_channel.h
  chrome/common/ipc_sync_message.cc
  chrome/common/ipc_sync_message.h
  chrome/common/thumbnail_score.h
)

SOURCE_GROUP(chrome\\common FILES ${CHROME_COMMON_SRCS})

#
# Google Chrome sandbox files:
#

SET(SECURITY_SRCS
  sandbox/src/acl.cc
  sandbox/src/acl.h
  sandbox/src/dep.cc
  sandbox/src/dep.h
  sandbox/src/job.cc
  sandbox/src/job.h
  sandbox/src/restricted_token.cc
  sandbox/src/restricted_token.h
  sandbox/src/restricted_token_utils.cc
  sandbox/src/restricted_token_utils.h
  sandbox/src/security_level.h
  sandbox/src/sid.cc
  sandbox/src/sid.h
  sandbox/src/window.cc
  sandbox/src/window.h
)

SOURCE_GROUP(sandbox\\security FILES ${SECURITY_SRCS})

SET(INTERCEPTION_SRCS
  sandbox/src/eat_resolver.cc
  sandbox/src/eat_resolver.h
  sandbox/src/interception.cc
  sandbox/src/interception.h
  sandbox/src/interception_agent.cc
  sandbox/src/interception_agent.h
  sandbox/src/interception_internal.h
  sandbox/src/pe_image.cc
  sandbox/src/pe_image.h
  sandbox/src/resolver.cc
  sandbox/src/resolver.h
  sandbox/src/service_resolver.cc
  sandbox/src/service_resolver.h
  sandbox/src/sidestep_resolver.cc
  sandbox/src/sidestep_resolver.h
  sandbox/src/target_interceptions.cc
  sandbox/src/target_interceptions.h
  sandbox/src/Wow64.cc
  sandbox/src/Wow64.h
)

SOURCE_GROUP(sandbox\\Interception FILES ${INTERCEPTION_SRCS})

SET(INTERCEPTION_SIDESTEP_SRCS
  sandbox/src/sidestep/ia32_modrm_map.cpp
  sandbox/src/sidestep/ia32_opcode_map.cpp
  sandbox/src/sidestep/mini_disassembler.cpp
  sandbox/src/sidestep/mini_disassembler.h
  sandbox/src/sidestep/mini_disassembler_types.h
  sandbox/src/sidestep/preamble_patcher.h
  sandbox/src/sidestep/preamble_patcher_with_stub.cpp
)

SOURCE_GROUP(sandbox\\Interception\\sidestep FILES ${INTERCEPTION_SIDESTEP_SRCS})

SET(NT_LEVEL_SRCS
  sandbox/src/nt_internals.h
  sandbox/src/policy_target.cc
  sandbox/src/policy_target.h
  sandbox/src/sandbox_nt_types.h
  sandbox/src/sandbox_nt_util.cc
  sandbox/src/sandbox_nt_util.h
)

SOURCE_GROUP(sandbox\\nt_level FILES ${NT_LEVEL_SRCS})

SET(POLICY_HANDLERS_SRCS
  sandbox/src/filesystem_dispatcher.cc
  sandbox/src/filesystem_dispatcher.h
  sandbox/src/filesystem_interception.cc
  sandbox/src/filesystem_interception.h
  sandbox/src/filesystem_policy.cc
  sandbox/src/filesystem_policy.h
  sandbox/src/named_pipe_dispatcher.cc
  sandbox/src/named_pipe_dispatcher.h
  sandbox/src/named_pipe_interception.cc
  sandbox/src/named_pipe_interception.h
  sandbox/src/named_pipe_policy.cc
  sandbox/src/named_pipe_policy.h
  sandbox/src/policy_params.h
  sandbox/src/process_thread_dispatcher.cc
  sandbox/src/process_thread_dispatcher.h
  sandbox/src/process_thread_interception.cc
  sandbox/src/process_thread_interception.h
  sandbox/src/process_thread_policy.cc
  sandbox/src/process_thread_policy.h
  sandbox/src/registry_dispatcher.cc
  sandbox/src/registry_dispatcher.h
  sandbox/src/registry_interception.cc
  sandbox/src/registry_interception.h
  sandbox/src/registry_policy.cc
  sandbox/src/registry_policy.h
  sandbox/src/sync_dispatcher.cc
  sandbox/src/sync_dispatcher.h
  sandbox/src/sync_interception.cc
  sandbox/src/sync_interception.h
  sandbox/src/sync_policy.cc
  sandbox/src/sync_policy.h
)

SOURCE_GROUP(sandbox\\Policy_handlers FILES ${POLICY_HANDLERS_SRCS})

SET(IPC_SRCS
  sandbox/src/crosscall_client.h
  sandbox/src/crosscall_params.h
  sandbox/src/crosscall_server.cc
  sandbox/src/crosscall_server.h
  sandbox/src/ipc_tags.h
  sandbox/src/sharedmem_ipc_client.cc
  sandbox/src/sharedmem_ipc_client.h
  sandbox/src/sharedmem_ipc_server.cc
  sandbox/src/sharedmem_ipc_server.h
)

SOURCE_GROUP(sandbox\\IPC FILES ${IPC_SRCS})

SET(POLICY_BASE_SRCS
  sandbox/src/policy_engine_opcodes.cc
  sandbox/src/policy_engine_opcodes.h
  sandbox/src/policy_engine_params.h
  sandbox/src/policy_engine_processor.cc
  sandbox/src/policy_engine_processor.h
  sandbox/src/policy_low_level.cc
  sandbox/src/policy_low_level.h
  sandbox/src/sandbox_policy_base.cc
  sandbox/src/sandbox_policy_base.h
)

SOURCE_GROUP(sandbox\\Policy_base FILES ${POLICY_BASE_SRCS})

SET(SANDBOX_SRCS
  sandbox/src/broker_services.cc
  sandbox/src/broker_services.h
  sandbox/src/internal_types.h
  sandbox/src/policy_broker.cc
  sandbox/src/policy_broker.h
  sandbox/src/sandbox.cc
  sandbox/src/sandbox.h
  sandbox/src/sandbox_factory.h
  sandbox/src/sandbox_policy.h
  sandbox/src/sandbox_types.h
  sandbox/src/sandbox_utils.cc
  sandbox/src/sandbox_utils.h
  sandbox/src/shared_handles.cc
  sandbox/src/shared_handles.h
  sandbox/src/target_process.cc
  sandbox/src/target_process.h
  sandbox/src/target_services.cc
  sandbox/src/target_services.h
  sandbox/src/win2k_threadpool.cc
  sandbox/src/win2k_threadpool.h
  sandbox/src/win_utils.cc
  sandbox/src/win_utils.h
)

SOURCE_GROUP(sandbox FILES ${SANDBOX_SRCS})

#
# Google Chrome bundled library:
#

ADD_LIBRARY(chrome STATIC
  ${DMG_FP_SRCS}
  ${NSPR_SRCS}
  ${BASE_SRCS}
  ${CHROME_COMMON_SRCS}
  ${SECURITY_SRCS}
  ${INTERCEPTION_SRCS}
  ${INTERCEPTION_SIDESTEP_SRCS}
  ${NT_LEVEL_SRCS}
  ${POLICY_HANDLERS_SRCS}
  ${IPC_SRCS}
  ${POLICY_BASE_SRCS}
  ${SANDBOX_SRCS}
)

TARGET_LINK_LIBRARIES(chrome
  dbghelp.lib psapi.lib ${GTEST_LIBRARIES}
)

SET_TARGET_PROPERTIES(chrome
  PROPERTIES
    RELEASE_OUTPUT_NAME chrome
    DEBUG_OUTPUT_NAME chromed
)

# Modeline for vim: set tw=79 et ts=4:

