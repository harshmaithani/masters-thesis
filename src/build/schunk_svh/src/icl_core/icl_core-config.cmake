# ===================================================================================
#  icl_core CMake configuration file
#
#             ** File generated automatically, do not modify **
#
#  Usage from an external project:
#    In your CMakeLists.txt, add these lines:
#
#    FIND_PACKAGE(icl_core REQUIRED )
#    TARGET_LINK_LIBRARIES(MY_TARGET_NAME ${icl_core_LIBRARIES})
#
#    This file will define the following variables:
#      - icl_core_LIBRARIES                 : The list of libraries to links against.
#      - icl_core_LIB_DIR              : The directory where lib files are. Calling LINK_DIRECTORIES
#                                              with this path is NOT needed.
#      - icl_core_INCLUDE_DIRS         : The include directories.
#
#    Advanced variables:
#      - icl_core_CONFIG_PATH
#
# =================================================================================================

# Extract the directory where *this* file has been installed (determined at cmake run-time)
get_filename_component(icl_core_CONFIG_PATH "${CMAKE_CURRENT_LIST_FILE}" PATH)

# Get the absolute path with no ../.. relative marks, to eliminate implicit linker warnings
get_filename_component(icl_core_INSTALL_PATH "${icl_core_CONFIG_PATH}/../.." REALPATH)

# ======================================================
# Include directories to add to the user project:
# ======================================================

# Provide the include directories to the caller
SET(icl_core_INCLUDE_DIRS "/home/harsh/catkin_ws/src/schunk_svh/src/icl_core/src")

# ======================================================
# Link directories to add to the user project:
# ======================================================

SET(icl_core_LIB_COMPONENTS icl_core;icl_core_config;icl_core_logging;icl_core_plugin;icl_core_thread;icl_core_dispatch)

# Provide the libs directory anyway, it may be needed in some cases.
SET(icl_core_LIB_DIR /home/harsh/catkin_ws/src/build/lib)
LINK_DIRECTORIES(${icl_core_LIB_DIR})

SET(icl_core_LIBRARIES "")
foreach(__ICLIB ${icl_core_LIB_COMPONENTS})
  SET(icl_core_LIBRARIES ${icl_core_LIBRARIES} ${__ICLIB})
  SET(${__ICLIB}_LIBRARY ${__ICLIB})
endforeach()

IF(WIN32)
  SET(icl_core_DEFINITIONS ${icl_core_DEFINITIONS} "-D_SYSTEM_WIN32_")
ENDIF(WIN32)

IF(UNIX)
  IF(NOT APPLE)
    SET(icl_core_DEFINITIONS ${icl_core_DEFINITIONS} "-D_SYSTEM_LINUX_" "-D_SYSTEM_POSIX_")
  ELSE()
    SET(icl_core_DEFINITIONS ${icl_core_DEFINITIONS} "-D_SYSTEM_DARWIN_" "-D_SYSTEM_POSIX_")
  ENDIF(NOT APPLE)
ENDIF(UNIX)
