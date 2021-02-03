cmake_minimum_required(VERSION 3.17)

project(BwatEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

add_subdirectory(lib)
include_directories(${BWATLIBS_HEADERS})

add_subdirectory(docs)

add_subdirectory(Engine)
include_directories(Engine)
add_subdirectory(Editor)

target_link_libraries(Editor Engine ${BWATLIBS_LIBS})