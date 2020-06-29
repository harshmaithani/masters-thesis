cmake_minimum_required(VERSION 2.8)
project( extrinsic_calibration )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS})

find_package(Boost REQUIRED COMPONENTS signals thread filesystem)
include_directories(${Boost_INCLUDE_DIRS})
  
add_executable(extrinsic_calibration src/extrinsic_calibration.cpp )
target_link_libraries( extrinsic_calibration ${OpenCV_LIBS})
