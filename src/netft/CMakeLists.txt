cmake_minimum_required(VERSION 2.8.3)
project(netft_rdt_driver)

find_package(catkin REQUIRED COMPONENTS 
  roscpp
  diagnostic_updater 
  diagnostic_msgs
  geometry_msgs
  rosbag
  std_msgs
)

find_package(Boost REQUIRED COMPONENTS 
  system 
  thread 
  program_options
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp diagnostic_updater diagnostic_msgs geometry_msgs
  LIBRARIES ${PROJECT_NAME}
)

include_directories(
  include
  ${Boost_INCLUDE_DIRS} 
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME} src/netft_rdt_driver.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${catkin_LIBRARIES})

add_executable(netft_node src/netft_node.cpp)
target_link_libraries(netft_node ${PROJECT_NAME} ${Boost_LIBRARIES} ${catkin_LIBRARIES})

add_executable(record_data_node src/record_data_node.cpp)
target_link_libraries(record_data_node ${Boost_LIBRARIES} ${catkin_LIBRARIES})

