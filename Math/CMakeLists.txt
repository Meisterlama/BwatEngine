cmake_minimum_required(VERSION 3.17)

project(Math LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(PRIVATE include)

option(MATH_INLINE_FUNCTIONS "Inlining the math library functions" ON)

file(GLOB_RECURSE BWAT_MATH_SRC
        *.cpp)

add_library(Math STATIC ${BWAT_MATH_SRC})
if (MATH_INLINE_FUNCTIONS)
    message(STATUS "Math library: Inlining functions")
    target_compile_definitions(Math PUBLIC -DINLINE_FUNCTIONS)
else()
    message(STATUS "Math library: Not inlining functions")
endif ()