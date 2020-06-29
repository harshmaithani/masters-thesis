# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "leap_client: 4 messages, 0 services")

set(MSG_I_FLAGS "-Ileap_client:/home/harsh/catkin_ws/src/leap_client/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg;-Ileap_client:/home/harsh/catkin_ws/src/leap_client/msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(leap_client_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/HandInfo.msg" NAME_WE)
add_custom_target(_leap_client_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "leap_client" "/home/harsh/catkin_ws/src/leap_client/msg/HandInfo.msg" "geometry_msgs/Point:leap_client/BoneInfo:geometry_msgs/Vector3:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Pose:leap_client/FingerInfo"
)

get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/HandInfoList.msg" NAME_WE)
add_custom_target(_leap_client_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "leap_client" "/home/harsh/catkin_ws/src/leap_client/msg/HandInfoList.msg" "geometry_msgs/Point:leap_client/FingerInfo:leap_client/BoneInfo:geometry_msgs/Vector3:geometry_msgs/Quaternion:geometry_msgs/Pose:leap_client/HandInfo:std_msgs/Header"
)

get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg" NAME_WE)
add_custom_target(_leap_client_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "leap_client" "/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg" "geometry_msgs/Vector3:std_msgs/Header"
)

get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg" NAME_WE)
add_custom_target(_leap_client_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "leap_client" "/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg" "geometry_msgs/Vector3:leap_client/BoneInfo:std_msgs/Header:geometry_msgs/Point"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(leap_client
  "/home/harsh/catkin_ws/src/leap_client/msg/HandInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/leap_client
)
_generate_msg_cpp(leap_client
  "/home/harsh/catkin_ws/src/leap_client/msg/HandInfoList.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg;/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/home/harsh/catkin_ws/src/leap_client/msg/HandInfo.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/leap_client
)
_generate_msg_cpp(leap_client
  "/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/leap_client
)
_generate_msg_cpp(leap_client
  "/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/leap_client
)

### Generating Services

### Generating Module File
_generate_module_cpp(leap_client
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/leap_client
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(leap_client_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(leap_client_generate_messages leap_client_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/HandInfo.msg" NAME_WE)
add_dependencies(leap_client_generate_messages_cpp _leap_client_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/HandInfoList.msg" NAME_WE)
add_dependencies(leap_client_generate_messages_cpp _leap_client_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg" NAME_WE)
add_dependencies(leap_client_generate_messages_cpp _leap_client_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg" NAME_WE)
add_dependencies(leap_client_generate_messages_cpp _leap_client_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(leap_client_gencpp)
add_dependencies(leap_client_gencpp leap_client_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS leap_client_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(leap_client
  "/home/harsh/catkin_ws/src/leap_client/msg/HandInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/leap_client
)
_generate_msg_lisp(leap_client
  "/home/harsh/catkin_ws/src/leap_client/msg/HandInfoList.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg;/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/home/harsh/catkin_ws/src/leap_client/msg/HandInfo.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/leap_client
)
_generate_msg_lisp(leap_client
  "/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/leap_client
)
_generate_msg_lisp(leap_client
  "/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/leap_client
)

### Generating Services

### Generating Module File
_generate_module_lisp(leap_client
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/leap_client
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(leap_client_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(leap_client_generate_messages leap_client_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/HandInfo.msg" NAME_WE)
add_dependencies(leap_client_generate_messages_lisp _leap_client_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/HandInfoList.msg" NAME_WE)
add_dependencies(leap_client_generate_messages_lisp _leap_client_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg" NAME_WE)
add_dependencies(leap_client_generate_messages_lisp _leap_client_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg" NAME_WE)
add_dependencies(leap_client_generate_messages_lisp _leap_client_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(leap_client_genlisp)
add_dependencies(leap_client_genlisp leap_client_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS leap_client_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(leap_client
  "/home/harsh/catkin_ws/src/leap_client/msg/HandInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/leap_client
)
_generate_msg_py(leap_client
  "/home/harsh/catkin_ws/src/leap_client/msg/HandInfoList.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg;/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/home/harsh/catkin_ws/src/leap_client/msg/HandInfo.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/leap_client
)
_generate_msg_py(leap_client
  "/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/leap_client
)
_generate_msg_py(leap_client
  "/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/leap_client
)

### Generating Services

### Generating Module File
_generate_module_py(leap_client
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/leap_client
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(leap_client_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(leap_client_generate_messages leap_client_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/HandInfo.msg" NAME_WE)
add_dependencies(leap_client_generate_messages_py _leap_client_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/HandInfoList.msg" NAME_WE)
add_dependencies(leap_client_generate_messages_py _leap_client_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/BoneInfo.msg" NAME_WE)
add_dependencies(leap_client_generate_messages_py _leap_client_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/harsh/catkin_ws/src/leap_client/msg/FingerInfo.msg" NAME_WE)
add_dependencies(leap_client_generate_messages_py _leap_client_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(leap_client_genpy)
add_dependencies(leap_client_genpy leap_client_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS leap_client_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/leap_client)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/leap_client
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(leap_client_generate_messages_cpp std_msgs_generate_messages_cpp)
add_dependencies(leap_client_generate_messages_cpp geometry_msgs_generate_messages_cpp)
add_dependencies(leap_client_generate_messages_cpp leap_client_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/leap_client)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/leap_client
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(leap_client_generate_messages_lisp std_msgs_generate_messages_lisp)
add_dependencies(leap_client_generate_messages_lisp geometry_msgs_generate_messages_lisp)
add_dependencies(leap_client_generate_messages_lisp leap_client_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/leap_client)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/leap_client\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/leap_client
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(leap_client_generate_messages_py std_msgs_generate_messages_py)
add_dependencies(leap_client_generate_messages_py geometry_msgs_generate_messages_py)
add_dependencies(leap_client_generate_messages_py leap_client_generate_messages_py)
