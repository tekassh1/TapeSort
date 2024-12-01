cmake_minimum_required(VERSION 3.10)

project(Tests VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE TESTS *.cpp)
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_executable(Tests ${TESTS} ${SOURCES})
target_include_directories(Tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(Tests gtest)
