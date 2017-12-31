cmake_minimum_required(VERSION 3.8)
project(korselt)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(tests)

set(SOURCE_FILES korselt/main.cpp korselt/korselt.h korselt/korselt.cpp)

add_executable(korselt ${SOURCE_FILES})