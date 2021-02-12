cmake_minimum_required(VERSION 3.17)

project(TestSuite LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC
        *.cpp)

add_executable(TestSuite ${SRC})
target_link_libraries(TestSuite PUBLIC gtest gtest_main Engine)