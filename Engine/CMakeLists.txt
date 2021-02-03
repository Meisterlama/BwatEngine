cmake_minimum_required(VERSION 3.17)

project(Engine LANGUAGES C CXX)

file(GLOB_RECURSE BWAT_ENGINE_SRC
        *.cpp)

add_library(Engine STATIC ${BWAT_ENGINE_SRC})
