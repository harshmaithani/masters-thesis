cmake_minimum_required(VERSION 2.8.3)
project(mtools_trajectory)

# find components
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(catkin REQUIRED COMPONENTS mtools_data_backup mtools_maths)
find_package(Eigen REQUIRED)
# note : eigen is a header-only lib, no need to link the project with its lib.

# declare catkin pkg
catkin_package(
  INCLUDE_DIRS include ${EIGEN_INCLUDE_DIRS}
  LIBRARIES ${PROJECT_NAME}
)

#build
include_directories(include ${catkin_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIRS})

add_library(${PROJECT_NAME} 
   src/JointTrajViaPoints.cpp
   src/CartTrajViaPoints.cpp)
target_link_libraries(${PROJECT_NAME}  ${catkin_LIBRARIES})

add_executable(JointTrajViaPoints_test test/JointTrajViaPoints_test.cpp) 
target_link_libraries(JointTrajViaPoints_test ${PROJECT_NAME} ${catkin_LIBRARIES})

add_executable(CartTrajViaPoints_test test/CartTrajViaPoints_test.cpp) 
target_link_libraries(CartTrajViaPoints_test ${PROJECT_NAME}  ${catkin_LIBRARIES})
