add_executable(robot-test
  main.cpp
  "${PROJECT_SOURCE_DIR}/src/robot/hello.test.cpp"
)

target_include_directories(robot-test PRIVATE "${PROJECT_SOURCE_DIR}/src")

target_compile_features(robot-test PRIVATE cxx_std_17)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.4
)
FetchContent_MakeAvailable(Catch2)

target_link_libraries(robot-test PRIVATE Catch2::Catch2)

list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/contrib")
include(Catch)
catch_discover_tests(robot-test)
