cmake_minimum_required(VERSION 3.17)

project(BwatEngine)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib)
include_directories(${BWATLIBS_HEADERS})

add_subdirectory(docs)

file(GLOB_RECURSE BWAT_ENGINE_SRC
        src/*.cpp)

add_executable(BwatEngine ${BWAT_ENGINE_SRC})
message(STATUS "${BWATLIBS_LIBS}")
target_link_libraries(BwatEngine PUBLIC ${BWATLIBS_LIBS})