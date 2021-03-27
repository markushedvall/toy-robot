cmake_minimum_required(VERSION 3.14)
project(robot LANGUAGES CXX)

option(WERROR "All warnings will be treated as errors" OFF)
option(LINT "Lint the code with clang-tidy" OFF)
option(COVERAGE "Build with coverage" OFF)

add_executable(robot
  src/robot/main.cpp
  src/robot/hello.cpp
)
target_include_directories(robot PRIVATE "${PROJECT_SOURCE_DIR}/src")

add_library(options INTERFACE)
target_compile_features(options INTERFACE cxx_std_17)

add_library(cov INTERFACE)
if(COVERAGE)
  target_compile_options(cov INTERFACE --coverage -O0 -g)
  target_link_options(cov INTERFACE --coverage)
endif()

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

target_link_libraries(robot PRIVATE options warnings cov)

if(LINT)
  find_program(CLANG_TIDY clang-tidy REQUIRED)
  if(WERROR)
    set(CLANG_TIDY_WERROR --warnings-as-errors=*)
  endif()
  set(CLANG_TIDY_CMD "${CLANG_TIDY}" ${CLANG_TIDY_WERROR} --quiet)

  if(CMAKE_GENERATOR MATCHES "Makefiles" OR CMAKE_GENERATOR MATCHES "Ninja")
    set_target_properties(robot PROPERTIES CXX_CLANG_TIDY ${CLANG_TIDY_CMD})
  else()
    get_target_property(TARGET_SOURCES robot SOURCES)

    foreach(TARGET_SOURCE ${TARGET_SOURCES})
      if(NOT IS_ABSOLUTE "${TARGET_SOURCE}")
        list(APPEND CLANG_TIDY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_SOURCE}")
      else()
        list(APPEND CLANG_TIDY_SOURCES "${TARGET_SOURCE}")
      endif()
    endforeach()

    add_custom_command(TARGET robot POST_BUILD
      COMMAND_EXPAND_LISTS
      COMMAND ${CLANG_TIDY_CMD} ${CLANG_TIDY_SOURCES} -- -std=c++17
              "-I$<JOIN:$<TARGET_PROPERTY:robot,INCLUDE_DIRECTORIES>,;-I>"
    )
  endif()
endif()

enable_testing()
add_subdirectory(tests)
