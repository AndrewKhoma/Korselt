cmake_minimum_required(VERSION 3.8)
project(google_test)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

include_directories(../../googletest/googletest/include)

set(SOURCE_FILES tests.cpp ../korselt/korselt.h ../korselt/korselt.cpp)
add_executable(google_test ${SOURCE_FILES})

target_link_libraries(google_test gtest gtest_main)