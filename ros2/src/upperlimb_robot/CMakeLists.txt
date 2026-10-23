cmake_minimum_required(VERSION 3.8)
project(upperlimb_robot)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ========================================
# Dependencies
# ========================================
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(ament_index_cpp REQUIRED)

# ========================================
# ROS2 Interfaces
# ========================================
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/ControlCommand.msg"
  "msg/RobotState.msg"
  "msg/SystemState.msg"
  "msg/SsvepResult.msg"
  "msg/SsvepActionStatus.msg"
  DEPENDENCIES builtin_interfaces
)

ament_export_dependencies(rosidl_default_runtime)

# 把 pinocchio / Eigen3 放到这里
find_package(pinocchio REQUIRED)
find_package(Eigen3 REQUIRED)

# ========================================
# Library paths
# ========================================
set(GOOGOLTECH_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(GOOGOLTECH_LIBS
  ${GOOGOLTECH_LIB_DIR}/libgxn_x64.so
  ${GOOGOLTECH_LIB_DIR}/libgt_rn_x64.so
  ${GOOGOLTECH_LIB_DIR}/libGLink_x64.so
  ${GOOGOLTECH_LIB_DIR}/libMachineBuilding_x64.so
  ${GOOGOLTECH_LIB_DIR}/libLAFunc_x64.so
  ${GOOGOLTECH_LIB_DIR}/libecat_master.so
  ${GOOGOLTECH_LIB_DIR}/libecat_config.so
  ${GOOGOLTECH_LIB_DIR}/libecfg_parser.so
)

add_library(upperlimb_control_algorithms SHARED
  src/control_algorithms.cpp
)

target_include_directories(upperlimb_control_algorithms PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${EIGEN3_INCLUDE_DIRS}
)

target_compile_features(upperlimb_control_algorithms PUBLIC cxx_std_17)

ament_target_dependencies(upperlimb_control_algorithms
  ament_index_cpp
)

target_link_libraries(upperlimb_control_algorithms
  pinocchio::pinocchio
  Eigen3::Eigen
)

add_executable(robot_control_node
  src/robot_control_node.cpp
)

target_include_directories(robot_control_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${EIGEN3_INCLUDE_DIRS}
)

target_compile_features(robot_control_node PUBLIC c_std_99 cxx_std_17)

ament_target_dependencies(robot_control_node
  rclcpp
  sensor_msgs
  ament_index_cpp
)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

target_link_libraries(robot_control_node
  "${cpp_typesupport_target}"
  upperlimb_control_algorithms
  ${GOOGOLTECH_LIBS}
)

install(TARGETS
  upperlimb_control_algorithms
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

# robot_control_node 是运行入口，不应作为下游包的可链接库导出。
install(TARGETS robot_control_node
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY include/
  DESTINATION include/
)

install(
  DIRECTORY msg/
  DESTINATION share/${PROJECT_NAME}/msg
)

install(
  DIRECTORY lib/
  DESTINATION share/${PROJECT_NAME}/lib
)

install(
  DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/config
)

install(
  FILES config/Gecat.eni
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY urdf/
  DESTINATION share/${PROJECT_NAME}/urdf
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  # 保留原机器人源码风格，且 gxn.h 为厂商头文件，避免 uncrustify 对其做全文件重排。
  set(ament_cmake_uncrustify_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  ament_add_gtest(test_ssvep_control
    test/test_ssvep_control.cpp
  )
  if(TARGET test_ssvep_control)
    target_link_libraries(test_ssvep_control upperlimb_control_algorithms)
    target_include_directories(test_ssvep_control PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
  endif()
endif()

ament_package()
