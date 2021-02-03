cmake_minimum_required(VERSION 3.17)

project(BwatEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib)
include_directories(${BWATLIBS_HEADERS})

add_subdirectory(docs)

add_subdirectory(Math)
include_directories(Math/include)

#TODO: Add game building target and ability to switch between editor and game

#TODO: Uncomment this when some source code for Engine is available
#add_subdirectory(Engine)
#include_directories(Engine)
add_subdirectory(Editor)

target_link_libraries(Editor ${BWATLIBS_LIBS})
#target_link_libraries(Editor Engine)