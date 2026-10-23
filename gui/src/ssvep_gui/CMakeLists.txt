cmake_minimum_required(VERSION 3.8)
project(ssvep_gui)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(upperlimb_robot REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
add_executable(ssvep_gui_node src/main.cpp)
target_compile_features(ssvep_gui_node PUBLIC cxx_std_17)
ament_target_dependencies(ssvep_gui_node rclcpp upperlimb_robot)
target_link_libraries(ssvep_gui_node Qt5::Widgets)
install(TARGETS ssvep_gui_node DESTINATION lib/${PROJECT_NAME})
ament_package()
