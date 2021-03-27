add_executable(robot-test
  main.cpp
  "${PROJECT_SOURCE_DIR}/src/robot/hello.cpp"
  "${PROJECT_SOURCE_DIR}/src/robot/hello.test.cpp"
)

target_include_directories(robot-test PRIVATE "${PROJECT_SOURCE_DIR}/src")

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.4
)
FetchContent_MakeAvailable(Catch2)

target_link_libraries(robot-test PRIVATE Catch2::Catch2 options warnings)

# if(COVERAGE)
#   target_compile_options(robot-test PRIVATE --coverage)
#   target_link_options(robot-test PRIVATE --coverage)
# endif()

list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/contrib")
include(Catch)
catch_discover_tests(robot-test)
