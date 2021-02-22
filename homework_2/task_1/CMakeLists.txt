cmake_minimum_required(VERSION 3.10)
project(guessing_game)

set(CMAKE_CXX_STANDARD 17)
#  generate compiple commands file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall")

## SET FOLDER
# set executables folder
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(task_1 src/main.cpp)