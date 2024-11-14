cmake_minimum_required(VERSION 3.5)
project(simple_examples_cpp)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(simple_interfaces REQUIRED) # Our own Interface
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)

# For server
add_library(server_lib SHARED 
  src/services/simple_server.cpp)
ament_target_dependencies(server_lib
  "simple_interfaces"
  "rclcpp"
  "rclcpp_components")
rclcpp_components_register_node(server_lib
  PLUGIN "simple_server_node::SimpleServerNode"
  EXECUTABLE simple_server)
install(TARGETS
  server_lib
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

# For client
add_executable(simple_client src/services/simple_client.cpp)
ament_target_dependencies(simple_client
  "simple_interfaces"
  "rclcpp")
install(TARGETS simple_client
  DESTINATION lib/${PROJECT_NAME})

ament_package()
