cmake_minimum_required(VERSION 3.17)

project(Editor LANGUAGES C CXX)

file(GLOB_RECURSE BWAT_EDITOR_SRC
        src/*.cpp)

add_executable(Editor ${BWAT_EDITOR_SRC})