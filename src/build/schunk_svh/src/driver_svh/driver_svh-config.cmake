# ===================================================================================
#  driver_svh CMake configuration file
#
#             ** File generated automatically, do not modify **
#
#  Usage from an external project:
#    In your CMakeLists.txt, add these lines:
#
#    FIND_PACKAGE(driver_svh REQUIRED )
#    TARGET_LINK_LIBRARIES(MY_TARGET_NAME ${driver_svh_LIBRARIES})
#
#    This file will define the following variables:
#      - driver_svh_LIBRARIES            : The list of libraries to links against.
#      - driver_svh_LIB_DIR              : The directory where lib files are. Calling LINK_DIRECTORIES
#                                                                with this path is NOT needed.
#      - driver_svh_INCLUDE_DIRS         : The include directories.
#
#    Advanced variables:
#      - driver_svh_CONFIG_PATH
#
# =================================================================================================

# Extract the directory where *this* file has been installed (determined at cmake run-time)
get_filename_component(driver_svh_CONFIG_PATH "${CMAKE_CURRENT_LIST_FILE}" PATH)

# Get the absolute path with no ../.. relative marks, to eliminate implicit linker warnings
get_filename_component(driver_svh_INSTALL_PATH "${driver_svh_CONFIG_PATH}/../.." REALPATH)

# ======================================================
# Include directories to add to the user project:
# ======================================================

# Provide the include directories to the caller
SET(driver_svh_INCLUDE_DIRS "/home/harsh/catkin_ws/src/schunk_svh/src/driver_svh/src")

# ======================================================
# Link directories to add to the user project:
# ======================================================

SET(driver_svh_LIB_COMPONENTS driver_svh)

# Provide the libs directory anyway, it may be needed in some cases.
SET(driver_svh_LIB_DIR /home/harsh/catkin_ws/src/build/lib)
LINK_DIRECTORIES(${driver_svh_LIB_DIR})

SET(driver_svh_LIBRARIES "")
foreach(__ICLIB ${driver_svh_LIB_COMPONENTS})
  SET(driver_svh_LIBRARIES ${driver_svh_LIBRARIES} ${__ICLIB})
endforeach()
