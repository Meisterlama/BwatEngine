cmake_minimum_required(VERSION 3.17)

project(BwatEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(BWAT_ENGINE_TEST_ENABLED OFF)
set(BWAT_EDITOR_ENABLED ON)


add_subdirectory(lib)
if(BWAT_ENGINE_TEST_ENABLED)
    add_subdirectory(tests)
endif()

add_subdirectory(Engine)
set(ENGINE_LIBRARY glad glfw assimp flatbuffers imgui OpenAL stb)

add_subdirectory(Game)
target_link_libraries(Game PUBLIC ${ENGINE_LIBRARY})
target_link_libraries(Game INTERFACE Engine)

add_subdirectory(Editor)
target_link_libraries(Editor PUBLIC ${ENGINE_LIBRARY})
target_link_libraries(Editor INTERFACE Engine)

target_link_libraries(Engine PUBLIC Game ${ENGINE_LIBRARY})

add_executable(Launcher launcher.cpp)
target_link_libraries(Launcher PUBLIC Engine)
if(BWAT_EDITOR_ENABLED)
    target_link_libraries(Engine PUBLIC Editor)
    target_link_libraries(Launcher PUBLIC Editor)
    target_compile_definitions(Launcher PRIVATE BWATEDITOR)
endif()