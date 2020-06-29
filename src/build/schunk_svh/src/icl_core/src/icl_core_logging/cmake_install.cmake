# Install script for directory: /home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging

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
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_logging.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_logging.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_logging.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/harsh/catkin_ws/src/build/devel/lib/libicl_core_logging.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_logging.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_logging.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_logging.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_logging.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/icl_core_logging" TYPE FILE FILES
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/icl_core_logging.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/ImportExport.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/Constants.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/FileLogOutput.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/Logging.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/LoggingMacros_LLOGGING.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/LoggingMacros_LLOGGING_FMT.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/LoggingMacros_LOGGING.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/LoggingMacros_LOGGING_FMT.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/LoggingMacros_MLOGGING.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/LoggingMacros_MLOGGING_FMT.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/LoggingMacros_SLOGGING.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/LoggingMacros_SLOGGING_FMT.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/LoggingManager.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/LogLevel.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/LogOutputStream.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/LogStream.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/ScopedSemaphore.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/ScopedTimer.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/Semaphore.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/SingletonThreadingModels.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/StdErrorLogOutput.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/StdLogOutput.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/Thread.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/ThreadStream.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tFileLogOutput.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tLoggingManager.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tLogLevel.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tLogOutputStream.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tLogStream.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tSemaphore.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tScopedSemaphore.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tStdErrorLogOutput.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tStdLogOutput.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tThreadStream.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tFileLogOutput.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tSemaphore.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tStdLogOutput.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tStdErrorLogOutput.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/tThread.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/stream_operators_impl_posix.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/ThreadImplPosix.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/UdpLogOutput.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/SemaphoreImplPosix.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/SQLiteLogDb.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_logging/SQLiteLogOutput.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")

