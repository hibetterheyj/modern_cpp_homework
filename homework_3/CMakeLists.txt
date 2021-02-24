cmake_minimum_required(VERSION 3.10)
project(homework_3)

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
link_directories()
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# set executables folder
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

## COMPILATION
add_library(html_writer src/html_writer.cpp)
add_library(image_brower src/image_brower.cpp)
add_executable(create_image_browser src/create_image_browser.cpp)
target_link_libraries(create_image_browser html_writer image_brower)
