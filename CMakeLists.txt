cmake_minimum_required(VERSION 3.17)

project(BwatEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif ()

if(LINUX)
    message(STATUS ">>> Linux ${CMAKE_SYSTEM}")
    add_definitions(-DLINUX)
elseif(WIN32)
    add_definitions(-DWIN32)
    message(STATUS ">>> Not Linux ${CMAKE_SYSTEM}")
else()
    message(FATAL_ERROR ">>> Not supported platform ${CMAKE_SYSTEM}")
endif()

option(BWAT_ENGINE_TEST_ENABLED OFF)
option(BWAT_EDITOR_ENABLED OFF)

    add_subdirectory(lib)
if(BWAT_ENGINE_TEST_ENABLED)
    add_subdirectory(tests)
endif()

#TODO: Include the directory properly
include_directories(lib/PhysX/physx/include lib/PhysX/pxshared/include/)
set(ENGINE_LIBRARY glad glfw assimp flatbuffers imgui OpenAL stb json dirent AudioFile lua sol2
        PhysXExtensions PhysX PhysXPvdSDK PhysXVehicle PhysXCharacterKinematic PhysXCooking PhysXCommon PhysXFoundation)
add_subdirectory(Engine)
target_link_libraries(Engine PUBLIC ${ENGINE_LIBRARY})
if(BWAT_EDITOR_ENABLED)
    target_compile_definitions(Engine PRIVATE BWATEDITOR)
endif()

add_subdirectory(Editor)
target_link_libraries(Editor PUBLIC ${ENGINE_LIBRARY})
target_link_libraries(Editor PUBLIC Engine)
if(BWAT_EDITOR_ENABLED)
    target_compile_definitions(Editor PRIVATE BWATEDITOR)
endif()

add_executable(Launcher launcher.cpp)
target_link_libraries(Launcher PUBLIC Engine)

if(BWAT_EDITOR_ENABLED)
    target_link_libraries(Engine PUBLIC Editor)
    target_link_libraries(Launcher PUBLIC Editor)
    target_compile_definitions(Launcher PRIVATE BWATEDITOR)
endif()
