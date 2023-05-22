cmake_minimum_required(VERSION 3.8)
project(image_manager)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
find_package(OpenCV 4.1 REQUIRED)
	
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(DIVISIBLE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(DIVISION_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${DIVISIBLE_INSTALL_INCLUDE_DIR})
include_directories(${DIVISION_SOURCE_DIR})

# add_executable(image_manager ${DIVISION_SOURCE_DIR}/image.cpp ${DIVISION_SOURCE_DIR}/io_tools.cpp)
# add serialize library
add_library(image  src/image.cpp src/io_tools.cpp)
enable_testing ()
add_subdirectory (tests)