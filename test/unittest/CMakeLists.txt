# @file CMakeLists.txt
# @author Samuel Macedo <samuel@comunip.com.br>
# @date 01/03/2009 10:57:05

# Copyright (c) 2010 ComunIP S/A. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

FIND_PACKAGE(GTest REQUIRED)

INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/chrome
  ${GTEST_INCLUDE_DIR}
  ${GMOCK_INCLUDE_DIR}
  ${BOOST_INCLUDE_DIR}
  ${BOOST_TR1_INCLUDE_DIR}
)

ADD_DEFINITIONS(-DNOMINMAX)

ADD_EXECUTABLE(mpm_unittest Main.cpp)
ADD_DEPENDENCIES(mpm_unittest mpm)
TARGET_LINK_LIBRARIES(mpm_unittest mpm ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})

# Modeline for vim: set tw=79 et ts=4:
