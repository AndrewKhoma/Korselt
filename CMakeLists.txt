cmake_minimum_required(VERSION 3.8)
project(korselt)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp korselt.h)

add_executable(korselt ${SOURCE_FILES})