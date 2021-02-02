cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 14)

project(BwatLibs LANGUAGES CXX C)


# ASSIMP BUILD
include_directories(PRIVATE assimp/include)

set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_GLTF_IMPORTER ON)
set(ASSIMP_BUILD_FBX_IMPORTER ON)
set(ASSIMP_NO_EXPORT ON)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_INSTALL OFF)

add_subdirectory(assimp)
list(APPEND BWATLIBS_HEADERS_INTERNAL "${CMAKE_CURRENT_SOURCE_DIR}/assimp/include")
list(APPEND BWATLIBS_LIBS_INTERNAL assimp)

# FLATBUFFERS BUILD
include_directories(PRIVATE flatbuffers/include)
set(FLATBUFFERS_BUILD_TESTS OFF)
set(FLATBUFFERS_STATIC_FLATC OFF)
set(FLATBUFFERS_INSTALL OFF)

add_subdirectory(flatbuffers)
list(APPEND BWATLIBS_HEADERS_INTERNAL "${CMAKE_CURRENT_SOURCE_DIR}/flatbuffers/include")
list(APPEND BWATLIBS_LIBS_INTERNAL flatbuffers)


# GLAD BUILD
include_directories(PRIVATE gladlib)

set(GLAD_SRC
        gladlib/glad/glad.c)

add_library(glad ${GLAD_SRC})
list(APPEND BWATLIBS_HEADERS_INTERNAL "${CMAKE_CURRENT_SOURCE_DIR}/gladlib")
list(APPEND BWATLIBS_LIBS_INTERNAL glad)

# GLFW BUILD
include_directories(PRIVATE glfw/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)
list(APPEND BWATLIBS_HEADERS_INTERNAL "${CMAKE_CURRENT_SOURCE_DIR}/glfw/include")
list(APPEND BWATLIBS_LIBS_INTERNAL glfw)

# GTEST BUILD
include_directories(PRIVATE googletest/googletest/include)

set(INSTALL_GTEST OFF)

add_subdirectory(googletest)
list(APPEND BWATLIBS_HEADERS_INTERNAL  "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include")
list(APPEND BWATLIBS_HEADERS_INTERNAL  "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include")

# IMGUI BUILD
include_directories(PRIVATE imgui/include)

set(IMGUI_SRC
        imgui/src/imgui.cpp
        imgui/src/imgui_demo.cpp
        imgui/src/imgui_draw.cpp
        imgui/src/imgui_impl_glfw.cpp
        imgui/src/imgui_impl_opengl3.cpp
        imgui/src/imgui_tables.cpp
        imgui/src/imgui_widgets.cpp)

add_library(imgui ${IMGUI_SRC})
list(APPEND BWATLIBS_HEADERS_INTERNAL  "${CMAKE_CURRENT_SOURCE_DIR}/imgui/include")
list(APPEND BWATLIBS_LIBS_INTERNAL imgui)

# OPENAL_SOFT BUILD
include_directories(PRIVATE openal-soft/include)

set(ALSOFT_UTILS OFF)
set(ALSOFT_INSTALL  OFF)
set(ALSOFT_INSTALL_CONFIG  OFF)
set(ALSOFT_INSTALL_HRTF_DATA  OFF)
set(ALSOFT_INSTALL_AMBDEC_PRESETS  OFF)
set(ALSOFT_INSTALL_EXAMPLES  OFF)
set(ALSOFT_INSTALL_UTILS  OFF)
set(ALSOFT_UPDATE_BUILD_VERSION  OFF)

add_subdirectory(openal-soft)
list(APPEND BWATLIBS_HEADERS_INTERNAL "${CMAKE_CURRENT_SOURCE_DIR}/openal-soft/include")
list(APPEND BWATLIBS_LIBS_INTERNAL OpenAL)

# STB BUILD
include_directories(PRIVATE stb/include)

set(STB_SRC
        stb/src/stb_image.cpp
        stb/src/stb_perlin.cpp
        )

add_library(stb ${STB_SRC})
list(APPEND BWATLIBS_HEADERS_INTERNAL "${CMAKE_CURRENT_SOURCE_DIR}/stb/include")
list(APPEND BWATLIBS_LIBS_INTERNAL stb)

# Sending headers to parent scope

set(BWATLIBS_HEADERS ${BWATLIBS_HEADERS_INTERNAL} PARENT_SCOPE)
set(BWATLIBS_LIBS ${BWATLIBS_LIBS_INTERNAL} PARENT_SCOPE)

