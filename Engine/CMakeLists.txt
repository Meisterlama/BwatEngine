cmake_minimum_required(VERSION 3.17)

project(Engine LANGUAGES C CXX)

include_directories(include)
include_directories(${BWATLIBS_HEADERS})

file(GLOB_RECURSE BWAT_ENGINE_SRC
        src/*.cpp)


file(GLOB_RECURSE BWAT_ENGINE_HEADERS
        include/*.hpp)

add_library(Engine STATIC ${BWAT_ENGINE_SRC} ${BWAT_ENGINE_HEADERS})
