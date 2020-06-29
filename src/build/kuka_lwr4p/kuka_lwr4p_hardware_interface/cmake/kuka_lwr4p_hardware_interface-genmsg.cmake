# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "kuka_lwr4p_hardware_interface: 0 messages, 2 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(kuka_lwr4p_hardware_interface_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StartRobot.srv" NAME_WE)
add_custom_target(_kuka_lwr4p_hardware_interface_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "kuka_lwr4p_hardware_interface" "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StartRobot.srv" ""
)

get_filename_component(_filename "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StopRobot.srv" NAME_WE)
add_custom_target(_kuka_lwr4p_hardware_interface_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "kuka_lwr4p_hardware_interface" "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StopRobot.srv" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(kuka_lwr4p_hardware_interface
  "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StartRobot.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kuka_lwr4p_hardware_interface
)
_generate_srv_cpp(kuka_lwr4p_hardware_interface
  "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StopRobot.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kuka_lwr4p_hardware_interface
)

### Generating Module File
_generate_module_cpp(kuka_lwr4p_hardware_interface
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kuka_lwr4p_hardware_interface
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(kuka_lwr4p_hardware_interface_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(kuka_lwr4p_hardware_interface_generate_messages kuka_lwr4p_hardware_interface_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StartRobot.srv" NAME_WE)
add_dependencies(kuka_lwr4p_hardware_interface_generate_messages_cpp _kuka_lwr4p_hardware_interface_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StopRobot.srv" NAME_WE)
add_dependencies(kuka_lwr4p_hardware_interface_generate_messages_cpp _kuka_lwr4p_hardware_interface_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(kuka_lwr4p_hardware_interface_gencpp)
add_dependencies(kuka_lwr4p_hardware_interface_gencpp kuka_lwr4p_hardware_interface_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS kuka_lwr4p_hardware_interface_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(kuka_lwr4p_hardware_interface
  "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StartRobot.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kuka_lwr4p_hardware_interface
)
_generate_srv_lisp(kuka_lwr4p_hardware_interface
  "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StopRobot.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kuka_lwr4p_hardware_interface
)

### Generating Module File
_generate_module_lisp(kuka_lwr4p_hardware_interface
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kuka_lwr4p_hardware_interface
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(kuka_lwr4p_hardware_interface_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(kuka_lwr4p_hardware_interface_generate_messages kuka_lwr4p_hardware_interface_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StartRobot.srv" NAME_WE)
add_dependencies(kuka_lwr4p_hardware_interface_generate_messages_lisp _kuka_lwr4p_hardware_interface_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StopRobot.srv" NAME_WE)
add_dependencies(kuka_lwr4p_hardware_interface_generate_messages_lisp _kuka_lwr4p_hardware_interface_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(kuka_lwr4p_hardware_interface_genlisp)
add_dependencies(kuka_lwr4p_hardware_interface_genlisp kuka_lwr4p_hardware_interface_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS kuka_lwr4p_hardware_interface_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(kuka_lwr4p_hardware_interface
  "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StartRobot.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kuka_lwr4p_hardware_interface
)
_generate_srv_py(kuka_lwr4p_hardware_interface
  "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StopRobot.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kuka_lwr4p_hardware_interface
)

### Generating Module File
_generate_module_py(kuka_lwr4p_hardware_interface
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kuka_lwr4p_hardware_interface
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(kuka_lwr4p_hardware_interface_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(kuka_lwr4p_hardware_interface_generate_messages kuka_lwr4p_hardware_interface_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StartRobot.srv" NAME_WE)
add_dependencies(kuka_lwr4p_hardware_interface_generate_messages_py _kuka_lwr4p_hardware_interface_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/harsh/catkin_ws/src/kuka_lwr4p/kuka_lwr4p_hardware_interface/srv/StopRobot.srv" NAME_WE)
add_dependencies(kuka_lwr4p_hardware_interface_generate_messages_py _kuka_lwr4p_hardware_interface_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(kuka_lwr4p_hardware_interface_genpy)
add_dependencies(kuka_lwr4p_hardware_interface_genpy kuka_lwr4p_hardware_interface_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS kuka_lwr4p_hardware_interface_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kuka_lwr4p_hardware_interface)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/kuka_lwr4p_hardware_interface
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(kuka_lwr4p_hardware_interface_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kuka_lwr4p_hardware_interface)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/kuka_lwr4p_hardware_interface
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(kuka_lwr4p_hardware_interface_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kuka_lwr4p_hardware_interface)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kuka_lwr4p_hardware_interface\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/kuka_lwr4p_hardware_interface
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(kuka_lwr4p_hardware_interface_generate_messages_py std_msgs_generate_messages_py)
