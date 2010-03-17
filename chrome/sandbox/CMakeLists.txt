# @file CMakeLists.txt
# @author Guilherme Versiani <guibv@comunip.com.br>
# @date 2/3/2010 10:49:52

# Copyright (c) 2010 ComunIP S/A. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

INCLUDE_DIRECTORIES(.. ${GTEST_INCLUDE_DIR})

SET(SECURITY_SRCS
  src/acl.cc
  src/acl.h
  src/dep.cc
  src/dep.h
  src/job.cc
  src/job.h
  src/restricted_token.cc
  src/restricted_token.h
  src/restricted_token_utils.cc
  src/restricted_token_utils.h
  src/security_level.h
  src/sid.cc
  src/sid.h
  src/window.cc
  src/window.h
)

SOURCE_GROUP(security FILES ${SECURITY_SRCS})

SET(INTERCEPTION_SRCS
  src/eat_resolver.cc
  src/eat_resolver.h
  src/interception.cc
  src/interception.h
  src/interception_agent.cc
  src/interception_agent.h
  src/interception_internal.h
  src/pe_image.cc
  src/pe_image.h
  src/resolver.cc
  src/resolver.h
  src/service_resolver.cc
  src/service_resolver.h
  src/sidestep_resolver.cc
  src/sidestep_resolver.h
  src/target_interceptions.cc
  src/target_interceptions.h
  src/Wow64.cc
  src/Wow64.h
)

SOURCE_GROUP(Interception FILES ${INTERCEPTION_SRCS})

SET(INTERCEPTION_SIDESTEP_SRCS
  src/sidestep/ia32_modrm_map.cpp
  src/sidestep/ia32_opcode_map.cpp
  src/sidestep/mini_disassembler.cpp
  src/sidestep/mini_disassembler.h
  src/sidestep/mini_disassembler_types.h
  src/sidestep/preamble_patcher.h
  src/sidestep/preamble_patcher_with_stub.cpp
)

SOURCE_GROUP(Interception\\sidestep FILES ${INTERCEPTION_SIDESTEP_SRCS})

SET(NT_LEVEL_SRCS
  src/nt_internals.h
  src/policy_target.cc
  src/policy_target.h
  src/sandbox_nt_types.h
  src/sandbox_nt_util.cc
  src/sandbox_nt_util.h
)

SOURCE_GROUP(nt_level FILES ${NT_LEVEL_SRCS})

SET(POLICY_HANDLERS_SRCS
  src/filesystem_dispatcher.cc
  src/filesystem_dispatcher.h
  src/filesystem_interception.cc
  src/filesystem_interception.h
  src/filesystem_policy.cc
  src/filesystem_policy.h
  src/named_pipe_dispatcher.cc
  src/named_pipe_dispatcher.h
  src/named_pipe_interception.cc
  src/named_pipe_interception.h
  src/named_pipe_policy.cc
  src/named_pipe_policy.h
  src/policy_params.h
  src/process_thread_dispatcher.cc
  src/process_thread_dispatcher.h
  src/process_thread_interception.cc
  src/process_thread_interception.h
  src/process_thread_policy.cc
  src/process_thread_policy.h
  src/registry_dispatcher.cc
  src/registry_dispatcher.h
  src/registry_interception.cc
  src/registry_interception.h
  src/registry_policy.cc
  src/registry_policy.h
  src/sync_dispatcher.cc
  src/sync_dispatcher.h
  src/sync_interception.cc
  src/sync_interception.h
  src/sync_policy.cc
  src/sync_policy.h
)

SOURCE_GROUP(Policy_handlers FILES ${POLICY_HANDLERS_SRCS})

SET(IPC_SRCS
  src/crosscall_client.h
  src/crosscall_params.h
  src/crosscall_server.cc
  src/crosscall_server.h
  src/ipc_tags.h
  src/sharedmem_ipc_client.cc
  src/sharedmem_ipc_client.h
  src/sharedmem_ipc_server.cc
  src/sharedmem_ipc_server.h
)

SOURCE_GROUP(IPC FILES ${IPC_SRCS})

SET(POLICY_BASE_SRCS
  src/policy_engine_opcodes.cc
  src/policy_engine_opcodes.h
  src/policy_engine_params.h
  src/policy_engine_processor.cc
  src/policy_engine_processor.h
  src/policy_low_level.cc
  src/policy_low_level.h
  src/sandbox_policy_base.cc
  src/sandbox_policy_base.h
)

SOURCE_GROUP(Policy_base FILES ${POLICY_BASE_SRCS})

SET(SANDBOX_SRCS
  src/broker_services.cc
  src/broker_services.h
  src/internal_types.h
  src/policy_broker.cc
  src/policy_broker.h
  src/sandbox.cc
  src/sandbox.h
  src/sandbox_factory.h
  src/sandbox_policy.h
  src/sandbox_types.h
  src/sandbox_utils.cc
  src/sandbox_utils.h
  src/shared_handles.cc
  src/shared_handles.h
  src/target_process.cc
  src/target_process.h
  src/target_services.cc
  src/target_services.h
  src/win2k_threadpool.cc
  src/win2k_threadpool.h
  src/win_utils.cc
  src/win_utils.h
)

ADD_LIBRARY(chrome_sandbox STATIC
  ${SECURITY_SRCS}
  ${INTERCEPTION_SRCS}
  ${INTERCEPTION_SIDESTEP_SRCS}
  ${NT_LEVEL_SRCS}
  ${POLICY_HANDLERS_SRCS}
  ${IPC_SRCS}
  ${POLICY_BASE_SRCS}
  ${SANDBOX_SRCS}
)
TARGET_LINK_LIBRARIES(chrome_sandbox ${GTEST_LIBRARIES})
SET_TARGET_PROPERTIES(chrome_sandbox
  PROPERTIES
    RELEASE_OUTPUT_NAME sandbox
    DEBUG_OUTPUT_NAME sandboxd
)

# Modeline for vim: set tw=79 et ts=4:
