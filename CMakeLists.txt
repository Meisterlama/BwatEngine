cmake_minimum_required(VERSION 3.17)

project(BwatEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(BWAT_ENGINE_TEST_ENABLED ON CACHE BOOL "" FORCE)

add_subdirectory(lib)
add_subdirectory(docs)

#TODO: Add game building target and ability to switch between editor and game

#TODO: Uncomment this when some source code for Engine is available
#add_subdirectory(Engine)
add_subdirectory(Editor)
target_link_libraries(Editor PUBLIC glad glfw assimp flatbuffers imgui OpenAL stb)
#target_link_libraries(Editor Engine)