cmake_minimum_required(VERSION 3.8)
project(oliver_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

find_package(onboarding_msgs REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(oliver_publisher src/oliver_publisher.cpp)
add_executable(oliver_subscriber src/oliver_subscriber.cpp)
ament_target_dependencies(oliver_publisher rclcpp onboarding_msgs)
ament_target_dependencies(oliver_subscriber rclcpp onboarding_msgs)

install(TARGETS
  oliver_publisher
  oliver_subscriber
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME})

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
