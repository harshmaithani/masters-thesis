# ===================================================================================
#  icl_comm CMake configuration file
#
#             ** File generated automatically, do not modify **
#
#  Usage from an external project:
#    In your CMakeLists.txt, add these lines:
#
#    FIND_PACKAGE(icl_comm REQUIRED )
#    TARGET_LINK_LIBRARIES(MY_TARGET_NAME ${icl_comm_LIBRARIES})
#
#    This file will define the following variables:
#      - icl_comm_LIBRARIES            : The list of libraries to links against.
#      - icl_comm_LIB_DIR              : The directory where lib files are. Calling LINK_DIRECTORIES
#                                                                with this path is NOT needed.
#      - icl_comm_INCLUDE_DIRS         : The include directories.
#
#    Advanced variables:
#      - icl_comm_CONFIG_PATH
#
# =================================================================================================

# Extract the directory where *this* file has been installed (determined at cmake run-time)
get_filename_component(icl_comm_CONFIG_PATH "${CMAKE_CURRENT_LIST_FILE}" PATH)

# Get the absolute path with no ../.. relative marks, to eliminate implicit linker warnings
get_filename_component(icl_comm_INSTALL_PATH "${icl_comm_CONFIG_PATH}/../.." REALPATH)

# ======================================================
# Include directories to add to the user project:
# ======================================================

# Provide the include directories to the caller
SET(icl_comm_INCLUDE_DIRS "/home/harsh/catkin_ws/src/schunk_svh/src/icl_comm/src")

# ======================================================
# Link directories to add to the user project:
# ======================================================

SET(icl_comm_LIB_COMPONENTS icl_comm;icl_comm_serial)

# Provide the libs directory anyway, it may be needed in some cases.
SET(icl_comm_LIB_DIR /home/harsh/catkin_ws/src/build/lib)
LINK_DIRECTORIES(${icl_comm_LIB_DIR})

SET(icl_comm_LIBRARIES "")
foreach(__ICLIB ${icl_comm_LIB_COMPONENTS})
  SET(icl_comm_LIBRARIES ${icl_comm_LIBRARIES} ${__ICLIB})
endforeach()
