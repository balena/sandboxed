# @file CMakeLists.txt
# @author Samuel Macedo <samuel@comunip.com.br>
# @date 30/6/2009 10:54:56

# Copyright (c) 2010 ComunIP S/A. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

FIND_PACKAGE(Qt4)

IF(QT4_FOUND)

  FIND_PACKAGE(GTest REQUIRED)

  PROJECT(qtpoc)

  INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/chrome
    ${GTEST_INCLUDE_DIR}
  )

  # Begin Qt Stuff...

  ADD_DEFINITIONS( ${QT4_DEFINITIONS} )

  SET(QT_SOURCES_H
    MPMEventLoop.h
  )

  SET(QT_USE_QTUITOOLS TRUE)
  SET(QT_USE_QTWEBKIT TRUE)
  INCLUDE(${QT_USE_FILE})

  QT4_WRAP_CPP(QT_WRAPPED_H ${QT_SOURCES_H})

  # End of Qt Stuff...

  ADD_EXECUTABLE(qtpoc WIN32 Main.cpp ${QT_SOURCES_H} ${QT_WRAPPED_H})
  ADD_DEPENDENCIES(qtpoc sandboxed)
  TARGET_LINK_LIBRARIES(qtpoc sandboxed ${GTEST_LIBRARIES} ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY})

ENDIF(QT4_FOUND)

# Modeline for vim: set tw=79 et ts=4: 

