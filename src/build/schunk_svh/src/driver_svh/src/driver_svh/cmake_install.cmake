# Install script for directory: /home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh

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
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdriver_svh.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdriver_svh.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdriver_svh.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/harsh/catkin_ws/src/build/devel/lib/libdriver_svh.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdriver_svh.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdriver_svh.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdriver_svh.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdriver_svh.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/driver_svh" TYPE FILE FILES
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/ImportExport.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/Logging.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHController.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHSerialPacket.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHPositionSettings.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHCurrentSettings.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHFirmwareInfo.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHControllerFeedback.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHControllerState.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHControlCommand.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHFeedbackPollingThread.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHFingerManager.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHReceiveThread.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHSerialInterface.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHEncoderSettings.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src/driver_svh/SVHHomeSettings.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")

