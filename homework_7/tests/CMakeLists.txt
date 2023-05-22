find_package(GTest REQUIRED)

add_executable(test_kmeans test_kmeans.cpp test_data.cpp)
target_link_libraries(test_kmeans kmeans GTest::Main)
gtest_discover_tests(test_kmeans WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

 add_executable(test_bow_dictionary test_bow_dictionary.cpp)
 target_link_libraries(test_bow_dictionary
                       bow_dictionary
                       serialization
                       GTest::Main)
 gtest_discover_tests(test_bow_dictionary WORKING_DIRECTORY
                      ${CMAKE_CURRENT_SOURCE_DIR})
