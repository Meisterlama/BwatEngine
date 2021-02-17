cmake_minimum_required(VERSION 3.17)

project(BwatEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(BWAT_ENGINE_TEST_ENABLED ON CACHE BOOL "" FORCE)

add_subdirectory(lib)
add_subdirectory(docs)
if(BWAT_ENGINE_TEST_ENABLED)
    add_subdirectory(tests)
endif()

#TODO: Add game building target and ability to switch between editor and game

add_subdirectory(Engine)
target_link_libraries(Engine PUBLIC glad glfw assimp flatbuffers imgui OpenAL stb)
add_subdirectory(Editor)
target_link_libraries(Editor PUBLIC Engine)