# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "pass_point_plan: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ipass_point_plan:/home/yuhang/planning_hkust/Pass_point/src/pass_point_plan/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(pass_point_plan_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/yuhang/planning_hkust/Pass_point/src/pass_point_plan/msg/Bspline.msg" NAME_WE)
add_custom_target(_pass_point_plan_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "pass_point_plan" "/home/yuhang/planning_hkust/Pass_point/src/pass_point_plan/msg/Bspline.msg" "geometry_msgs/Point"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(pass_point_plan
  "/home/yuhang/planning_hkust/Pass_point/src/pass_point_plan/msg/Bspline.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pass_point_plan
)

### Generating Services

### Generating Module File
_generate_module_cpp(pass_point_plan
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pass_point_plan
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(pass_point_plan_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(pass_point_plan_generate_messages pass_point_plan_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yuhang/planning_hkust/Pass_point/src/pass_point_plan/msg/Bspline.msg" NAME_WE)
add_dependencies(pass_point_plan_generate_messages_cpp _pass_point_plan_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pass_point_plan_gencpp)
add_dependencies(pass_point_plan_gencpp pass_point_plan_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pass_point_plan_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(pass_point_plan
  "/home/yuhang/planning_hkust/Pass_point/src/pass_point_plan/msg/Bspline.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pass_point_plan
)

### Generating Services

### Generating Module File
_generate_module_eus(pass_point_plan
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pass_point_plan
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(pass_point_plan_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(pass_point_plan_generate_messages pass_point_plan_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yuhang/planning_hkust/Pass_point/src/pass_point_plan/msg/Bspline.msg" NAME_WE)
add_dependencies(pass_point_plan_generate_messages_eus _pass_point_plan_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pass_point_plan_geneus)
add_dependencies(pass_point_plan_geneus pass_point_plan_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pass_point_plan_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(pass_point_plan
  "/home/yuhang/planning_hkust/Pass_point/src/pass_point_plan/msg/Bspline.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pass_point_plan
)

### Generating Services

### Generating Module File
_generate_module_lisp(pass_point_plan
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pass_point_plan
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(pass_point_plan_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(pass_point_plan_generate_messages pass_point_plan_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yuhang/planning_hkust/Pass_point/src/pass_point_plan/msg/Bspline.msg" NAME_WE)
add_dependencies(pass_point_plan_generate_messages_lisp _pass_point_plan_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pass_point_plan_genlisp)
add_dependencies(pass_point_plan_genlisp pass_point_plan_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pass_point_plan_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(pass_point_plan
  "/home/yuhang/planning_hkust/Pass_point/src/pass_point_plan/msg/Bspline.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pass_point_plan
)

### Generating Services

### Generating Module File
_generate_module_nodejs(pass_point_plan
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pass_point_plan
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(pass_point_plan_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(pass_point_plan_generate_messages pass_point_plan_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yuhang/planning_hkust/Pass_point/src/pass_point_plan/msg/Bspline.msg" NAME_WE)
add_dependencies(pass_point_plan_generate_messages_nodejs _pass_point_plan_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pass_point_plan_gennodejs)
add_dependencies(pass_point_plan_gennodejs pass_point_plan_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pass_point_plan_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(pass_point_plan
  "/home/yuhang/planning_hkust/Pass_point/src/pass_point_plan/msg/Bspline.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pass_point_plan
)

### Generating Services

### Generating Module File
_generate_module_py(pass_point_plan
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pass_point_plan
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(pass_point_plan_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(pass_point_plan_generate_messages pass_point_plan_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/yuhang/planning_hkust/Pass_point/src/pass_point_plan/msg/Bspline.msg" NAME_WE)
add_dependencies(pass_point_plan_generate_messages_py _pass_point_plan_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pass_point_plan_genpy)
add_dependencies(pass_point_plan_genpy pass_point_plan_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pass_point_plan_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pass_point_plan)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pass_point_plan
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(pass_point_plan_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(pass_point_plan_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pass_point_plan)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pass_point_plan
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(pass_point_plan_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(pass_point_plan_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pass_point_plan)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pass_point_plan
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(pass_point_plan_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(pass_point_plan_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pass_point_plan)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pass_point_plan
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(pass_point_plan_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(pass_point_plan_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pass_point_plan)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pass_point_plan\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pass_point_plan
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(pass_point_plan_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(pass_point_plan_generate_messages_py geometry_msgs_generate_messages_py)
endif()
