cmake_minimum_required(VERSION 3.10.0)

project(list_c VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_library(list_c SHARED src/list_c.c)
target_include_directories(list_c PUBLIC include)

#include(CTest)
enable_testing()

find_package(GTest REQUIRED)

add_executable(great_test 
    tests/great_test.cpp
)

target_link_libraries(great_test
    PRIVATE
    list_c
    GTest::gtest_main
    
)

include(GoogleTest)
gtest_discover_tests(great_test)
