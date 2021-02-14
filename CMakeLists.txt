cmake_minimum_required(VERSION 3.14)
project(robot LANGUAGES CXX)

add_executable(robot src/robot/main.cpp)
target_include_directories(robot PRIVATE "${PROJECT_SOURCE_DIR}/src")

target_compile_features(robot PRIVATE cxx_std_17)

enable_testing()
add_subdirectory(tests)
