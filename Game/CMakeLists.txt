cmake_minimum_required(VERSION 3.17)

project(Game LANGUAGES C CXX)

file(GLOB_RECURSE BWAT_GAME_SRC
        src/*.cpp)
file(GLOB_RECURSE BWAT_GAME_HEADERS
        include/*.hpp)

add_library(Game STATIC ${BWAT_GAME_SRC} ${BWAT_GAME_HEADERS})