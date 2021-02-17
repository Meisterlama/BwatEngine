cmake_minimum_required(VERSION 3.17)

project(Engine LANGUAGES C CXX)

file(GLOB_RECURSE BWAT_ENGINE_SRC
        src/*.cpp)

add_library(Engine STATIC ${BWAT_ENGINE_SRC})
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)