# ===================================================================================
#  tinyxml CMake configuration file
#
#             ** File generated automatically, do not modify **
#
#  Usage from an external project:
#    In your CMakeLists.txt, add these lines:
#
#    FIND_PACKAGE(tinyxml REQUIRED )
#    TARGET_LINK_LIBRARIES(MY_TARGET_NAME ${tinyxml_LIBRARIES})
#
#    This file will define the following variables:
#      - tinyxml_LIBRARIES                 : The list of libraries to links against.
#      - tinyxml_LIB_DIR              : The directory where lib files are. Calling LINK_DIRECTORIES
#                                              with this path is NOT needed.
#      - tinyxml_INCLUDE_DIRS         : The include directories.
#
#    Advanced variables:
#      - tinyxml_CONFIG_PATH
#
# =================================================================================================

# Extract the directory where *this* file has been installed (determined at cmake run-time)
get_filename_component(tinyxml_CONFIG_PATH "${CMAKE_CURRENT_LIST_FILE}" PATH)

# Get the absolute path with no ../.. relative marks, to eliminate implicit linker warnings
get_filename_component(tinyxml_INSTALL_PATH "${tinyxml_CONFIG_PATH}/../.." REALPATH)

# ======================================================
# Include directories to add to the user project:
# ======================================================

# Provide the include directories to the caller
SET(tinyxml_INCLUDE_DIRS "${tinyxml_INSTALL_PATH}/include")

# ======================================================
# Link directories to add to the user project:
# ======================================================

SET(tinyxml_LIB_COMPONENTS tinyxml)

# Provide the libs directory anyway, it may be needed in some cases.
SET(tinyxml_LIB_DIR "${tinyxml_INSTALL_PATH}/lib")
LINK_DIRECTORIES(${tinyxml_LIB_DIR})

SET(tinyxml_LIBRARIES "")
foreach(__ICLIB ${tinyxml_LIB_COMPONENTS})
  SET(tinyxml_LIBRARIES ${tinyxml_LIBRARIES} ${__ICLIB})
  SET(${__ICLIB}_LIBRARY ${__ICLIB})
endforeach()

SET(tinyxml_DEFINITIONS ${tinyxml_DEFINITIONS} "-DTIXML_USE_STL")
