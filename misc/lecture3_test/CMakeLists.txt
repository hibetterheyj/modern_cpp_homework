cmake_minimum_required(VERSION 3.10)
project(lecture3_test)

set(CMAKE_CXX_STANDARD 17)
#  generate compiple commands file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall")

## SET FOLDER
# set headers folder
#  c++ -I
include_directories(include/)
# set libs folder
# c++ -L
# link_directories()
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# set executables folder
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

## COMPILATION
add_executable(testbasics src/test.cpp)
add_executable(testfs src/test_filesystem.cpp)
