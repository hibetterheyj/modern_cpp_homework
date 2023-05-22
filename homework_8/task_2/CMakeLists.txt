cmake_minimum_required(VERSION 3.8)
project(image_stack)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
find_package(OpenCV 4.1 REQUIRED)
find_package(PNG REQUIRED) 	
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(DIVISIBLE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(DIVISION_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${DIVISIBLE_INSTALL_INCLUDE_DIR})
include_directories(${DIVISION_SOURCE_DIR})
include_directories(${PNG_INCLUDE_DIR})
add_library(strategies src/png_strategy.cpp src/ppm_strategy.cpp)
target_link_libraries(strategies  ${PNG_LIBRARY})

add_library(image  src/image.cpp)
target_link_libraries(image ${OpenCV_LIBRARIES} strategies)

enable_testing ()
add_subdirectory (tests)