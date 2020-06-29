# Install script for directory: /home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config

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
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_config.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_config.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_config.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/harsh/catkin_ws/src/build/devel/lib/libicl_core_config.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_config.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_config.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_config.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libicl_core_config.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/icl_core_config" TYPE FILE FILES
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/AttributeTree.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/Config.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ConfigEnum.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ConfigEnumDefault.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ConfigHelper.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ConfigIterator.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ConfigList.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ConfigManager.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ConfigObserver.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ConfigParameter.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ConfigPositionalParameter.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ConfigValue.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ConfigValueDefault.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ConfigValueIface.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ConfigValues.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/GetoptParameter.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/GetoptPositionalParameter.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/GetoptParser.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/icl_core_config.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/ImportExport.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/MemberEnum.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/MemberValue.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/MemberValueIface.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/Util.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/tConfig.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/tConfigIterator.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/tConfigObserver.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/tConfigParameter.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/tConfigValues.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/tGetopt.h"
    "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src/icl_core_config/tGetoptParameter.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")

