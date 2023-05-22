cmake_minimum_required(VERSION 3.8)
project(code_book)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
find_package(OpenCV 4.1 REQUIRED)
	
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(DIVISIBLE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(DIVISION_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${DIVISIBLE_INSTALL_INCLUDE_DIR})
include_directories(${DIVISION_SOURCE_DIR})

# add libraries
add_library(bow_dictionary src/bow_dictionary.cpp src/codebook.cpp)
target_link_libraries(bow_dictionary ${OpenCV_LIBRARIES}  stdc++fs)
add_library(histogram src/histogram.cpp)
target_link_libraries(histogram ${OpenCV_LIBRARIES}  bow_dictionary)

#unit tests
enable_testing ()
add_subdirectory (tests)