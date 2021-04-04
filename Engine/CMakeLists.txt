cmake_minimum_required(VERSION 3.17)

# not mandatory
project(Engine LANGUAGES C CXX)

file(GLOB_RECURSE BWAT_ENGINE_SRC
        *.cpp)
file(GLOB_RECURSE BWAT_ENGINE_HEADERS
        *.hpp)

# headers are not needed when defining a target
add_library(Engine STATIC ${BWAT_ENGINE_SRC} ${BWAT_ENGINE_HEADERS})
target_include_directories(Engine PUBLIC include)
