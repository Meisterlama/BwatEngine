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

set(BWAT_ENGINE_TEST_ENABLED OFF)
set(BWAT_EDITOR_ENABLED ON)
set(BWAT_EDITOR_DEBUG_ENABLED ON)


if(BWAT_EDITOR_DEBUG_ENABLED)
    add_compile_definitions(BWATDEBUG)
endif()


add_subdirectory(lib)
if(BWAT_ENGINE_TEST_ENABLED)
    add_subdirectory(tests)
endif()

#TODO: Include the directory properly
include_directories(lib/PhysX/physx/include lib/PhysX/pxshared/include/)

add_subdirectory(Engine)
set(ENGINE_LIBRARY glad glfw assimp flatbuffers imgui OpenAL stb json dirent AudioFile
PhysXExtensions PhysX PhysXPvdSDK PhysXVehicle PhysXCharacterKinematic PhysXCooking PhysXCommon PhysXFoundation)

add_subdirectory(Game)
target_link_libraries(Game PUBLIC ${ENGINE_LIBRARY})
target_link_libraries(Game PUBLIC Engine)

add_subdirectory(Editor)
target_link_libraries(Editor PUBLIC ${ENGINE_LIBRARY})
target_link_libraries(Editor PUBLIC Engine)

target_link_libraries(Engine PUBLIC Game ${ENGINE_LIBRARY})

file(GLOB_RECURSE BWATENGINE_ASSETS
        ${CMAKE_SOURCE_DIR}/Assets/*)

MESSAGE(STATUS "\n\n\nASSETS: ${BWATENGINE_ASSETS}")

add_executable(Launcher launcher.cpp)
target_link_libraries(Launcher PUBLIC Engine)
add_dependencies(Launcher Engine)
add_custom_command(TARGET Launcher
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Assets/ $<TARGET_FILE_DIR:Launcher>/Assets/
        DEPENDS ${BWATENGINE_ASSETS})

if(BWAT_EDITOR_ENABLED)
    target_link_libraries(Engine PUBLIC Editor)
    target_link_libraries(Launcher PUBLIC Editor)
    target_compile_definitions(Launcher PRIVATE BWATEDITOR)
endif()
