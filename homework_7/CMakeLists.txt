cmake_minimum_required(VERSION 3.8)
project(code_book)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
find_package(OpenCV 4.1 REQUIRED)
	
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
add_compile_options(-g)
set(DIVISIBLE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(DIVISION_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${DIVISIBLE_INSTALL_INCLUDE_DIR})
include_directories(${DIVISION_SOURCE_DIR})

 #add_executable(kmeans ${DIVISION_SOURCE_DIR}/codebook.cpp)
 #target_link_libraries(kmeans ${OpenCV_LIBRARIES})

# add  library
add_library(kmeans  src/codebook.cpp)
add_library(serialization  src/convert_dataset.cpp src/serialize.cpp)
add_library(bow_dictionary src/bow_dictionary.cpp)
target_link_libraries(kmeans ${OpenCV_LIBRARIES} serialization stdc++fs)
target_link_libraries(serialization ${OpenCV_LIBRARIES} stdc++fs)
target_link_libraries(bow_dictionary ${OpenCV_LIBRARIES} kmeans)
enable_testing ()
add_subdirectory (tests)