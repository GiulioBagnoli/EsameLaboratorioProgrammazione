cmake_minimum_required(VERSION 3.5)
project(matrici)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(test)

set(SOURCE_FILES Matrix.h Matrix.cpp main.cpp)
add_executable(matrici main.cpp)

add_library(core ${SOURCE_FILES})
target_link_libraries(matrici core)