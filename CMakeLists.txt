cmake_minimum_required(VERSION 2.8)
project(gmxcpp)
set (gmxcpp_VERSION_MAJOR 1)
set (gmxcpp_VERSION_MINOR 0)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")
add_subdirectory(include)
include_directories(include)
add_subdirectory(src)