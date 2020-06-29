execute_process(COMMAND "/home/harsh/catkin_ws/src/build/image_pipeline/camera_calibration/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/harsh/catkin_ws/src/build/image_pipeline/camera_calibration/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
