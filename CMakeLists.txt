cmake_minimum_required(VERSION 3.10)

project(TapeSort VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(TapeSort ${SOURCES})

target_include_directories(TapeSort PRIVATE include)