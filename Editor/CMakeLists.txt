cmake_minimum_required(VERSION 3.17)

project(Editor LANGUAGES C CXX)

file(GLOB_RECURSE BWAT_EDITOR_SRC
        src/*.cpp)

file(GLOB_RECURSE BWAT_EDITOR_HEADERS
        include/*.hpp)

add_library(Editor STATIC ${BWAT_EDITOR_SRC} ${BWAT_EDITOR_HEADERS})