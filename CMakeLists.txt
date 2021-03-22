cmake_minimum_required(VERSION 3.14)
project(robot LANGUAGES CXX)

option(WERROR "All warnings will be treated as errors" OFF)

add_executable(robot src/robot/main.cpp)
target_include_directories(robot PRIVATE "${PROJECT_SOURCE_DIR}/src")

add_library(options INTERFACE)
target_compile_features(options INTERFACE cxx_std_17)

add_library(warnings INTERFACE)
if(CMAKE_CXX_COMPILER_ID MATCHES Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(warnings INTERFACE -Wall -Wpedantic -Wextra)
  if (WERROR)
    target_compile_options(warnings INTERFACE -Werror)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
  target_compile_options(warnings INTERFACE /permissive /W4)
  if (WERROR)
    target_compile_options(warnings INTERFACE /WX)
  endif()
endif()

target_link_libraries(robot PRIVATE options warnings)

enable_testing()
add_subdirectory(tests)
