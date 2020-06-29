cmake_minimum_required(VERSION 2.8.3)
project(mtools_maths)

# find components
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(catkin REQUIRED COMPONENTS)
find_package(Eigen REQUIRED)

# declare catkin pkg
catkin_package(
  INCLUDE_DIRS include ${EIGEN_INCLUDE_DIRS}
  DEPENDS Eigen
)

#build
include_directories(include ${catkin_INCLUDE_DIRS} ${Eigen_INCLUDE_DIRS})

# trying to make header-only lib, avoid user to link lib.

