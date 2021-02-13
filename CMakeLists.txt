cmake_minimum_required(VERSION 3.8)
project(robot LANGUAGES CXX)

add_executable(robot src/robot/main.cpp)
target_compile_features(robot PRIVATE cxx_std_17)
