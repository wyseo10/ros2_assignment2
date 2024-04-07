cmake_minimum_required(VERSION 3.8)
project(ros2_assig2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)




#<node name> src/<file.cpp>
add_executable(talker src/pub.cpp)
ament_target_dependencies(talker rclcpp std_msgs geometry_msgs)

add_executable(listener src/sub.cpp)
ament_target_dependencies(listener rclcpp std_msgs turtlesim)

add_executable(move_square src/square.cpp)
ament_target_dependencies(move_square rclcpp std_msgs geometry_msgs)


install(TARGETS
  talker
  listener
  move_square
  DESTINATION lib/${PROJECT_NAME})
  
  install(DIRECTORY 
  launch
  DESTINATION share/${PROJECT_NAME}
)

target_include_directories(move_square PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(move_square PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()