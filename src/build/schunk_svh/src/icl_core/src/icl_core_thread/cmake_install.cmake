# Install script for directory: /home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/harsh/catkin_ws/src/export")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_thread.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_thread.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_thread.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/harsh/catkin_ws/src/build/devel/lib/libicl_core_thread.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_thread.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_thread.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_thread.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_thread.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/icl_core_thread" TYPE FILE FILES
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/ActiveObject.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/ActiveOperation.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/icl_core_thread.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/ImportExport.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/Mutex.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/PeriodicThread.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/RWLock.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/ScopedMutexLock.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/Sem.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/SingletonThreadingModels.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/Thread.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/tMutex.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/tPeriodicThread.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/tRWLock.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/tScopedMutexLock.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/tScopedRWLock.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/tSemaphore.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_thread/tThread.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")

