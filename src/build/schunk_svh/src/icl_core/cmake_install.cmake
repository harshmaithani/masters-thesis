# Install script for directory: /home/harsh/catkin_ws/src/schunk_svh/src/icl_core

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/icl_core" TYPE FILE FILES "/home/harsh/catkin_ws/src/build/unix-install/icl_core-config.cmake")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/icl_core/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/icl_core_config/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/icl_core_logging/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/icl_core_plugin/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/icl_core_thread/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/icl_core_testsuite/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/icl_core_dispatch/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/icl_core_crypt/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/uls/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/test/test_icl_core_config/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/test/test_icl_core_logging/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/ts/icl_core/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/ts/icl_core_config/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/ts/icl_core_thread/cmake_install.cmake")
  INCLUDE("/home/harsh/catkin_ws/src/build/schunk_svh/src/icl_core/src/ts/icl_core_crypt/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

