cmake_minimum_required(VERSION 3.5)
project(xml_valid)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(xml_valid ${SOURCE_FILES})