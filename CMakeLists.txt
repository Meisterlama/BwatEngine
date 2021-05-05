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

add_subdirectory(Engine)

add_executable(Launcher launcher.cpp)
target_link_libraries(Launcher PUBLIC Engine)

if(BWAT_EDITOR_ENABLED)
    add_subdirectory(Editor)
    target_link_libraries(Launcher PUBLIC Editor)
    target_compile_definitions(Launcher PRIVATE BWATEDITOR)
    target_compile_definitions(Editor PRIVATE BWATEDITOR)
    target_compile_definitions(Engine PRIVATE BWATEDITOR)
endif()