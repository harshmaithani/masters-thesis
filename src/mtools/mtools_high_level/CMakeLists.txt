cmake_minimum_required(VERSION 2.8.3)
project(mtools_high_level)

# activate C++11 features
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

## find catkin macros and libraries
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(catkin REQUIRED COMPONENTS
  kuka_lwr4p_controllers
  kuka_lwr4p_controllers_msgs
  mtools_maths
  tf
  sensor_msgs
  geometry_msgs
  roscpp
)

find_package(Eigen REQUIRED)

## catkin specific configuration
catkin_package() 

## build
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${EIGEN_INCLUDE_DIRS}
)


add_executable(kuka_cart_imp_replay src/kuka_cart_imp_replay.cpp) 
target_link_libraries(kuka_cart_imp_replay ${catkin_LIBRARIES}) 

add_executable(find_bracket_replay src/find_bracket_replay.cpp) 
target_link_libraries(find_bracket_replay ${catkin_LIBRARIES}) 

add_executable(find_bracket src/find_bracket.cpp) 
target_link_libraries(find_bracket ${catkin_LIBRARIES}) 
