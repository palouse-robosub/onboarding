cmake_minimum_required(VERSION 3.8)
project(ziang_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

find_package(onboarding_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs)
find_package(CURL REQUIRED)

add_executable(atmosphericpressure_publisher src/atmosphericpressure_publisher.cpp)
add_executable(atmosphericpressure_subscriber src/atmosphericpressure_subscriber.cpp)
ament_target_dependencies(atmosphericpressure_publisher rclcpp onboarding_msgs sensor_msgs )
ament_target_dependencies(atmosphericpressure_subscriber rclcpp onboarding_msgs sensor_msgs )

target_link_libraries(atmosphericpressure_publisher CURL::libcurl)
set_target_properties(atmosphericpressure_publisher PROPERTIES
  INSTALL_RPATH_USE_LINK_PATH TRUE
)

install(TARGETS
  atmosphericpressure_publisher
  atmosphericpressure_subscriber
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
