cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

project(BwatLibs LANGUAGES CXX C)

option(BWAT_ENGINE_TEST_ENABLED "Whether or not we are running the test of BwatEngine" OFF)

# ASSIMP BUILD
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(assimp)

# FLATBUFFERS BUILD
set(FLATBUFFERS_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(FLATBUFFERS_STATIC_FLATC ON CACHE BOOL "" FORCE)
set(FLATBUFFERS_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(flatbuffers)

# GLAD BUILD
include_directories(PRIVATE gladlib)
set(GLAD_SRC
        gladlib/glad/glad.c)

add_library(glad STATIC ${GLAD_SRC})
target_include_directories(glad PUBLIC gladlib)

# GLFW BUILD
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)
#For some reasons the next line breaks everything
#target_compile_definitions(glfw PRIVATE -DGLFW_INCLUDE_NONE)

# GTEST BUILD
if (BWAT_ENGINE_TEST_ENABLED)
    include_directories(PRIVATE googletest/googletest/include)

    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

    add_subdirectory(googletest)
endif()

# IMGUI BUILD
set(IMGUI_SRC
        imgui/src/imgui.cpp
        imgui/src/imgui_demo.cpp
        imgui/src/imgui_draw.cpp
        imgui/src/imgui_impl_glfw.cpp
        imgui/src/imgui_impl_opengl3.cpp
        imgui/src/imgui_tables.cpp
        imgui/src/imgui_widgets.cpp)

add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC imgui/include)
target_link_libraries(imgui PUBLIC glfw glad)

# OPENAL_SOFT BUILD
set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ALSOFT_INSTALL  OFF CACHE BOOL "" FORCE)
set(ALSOFT_INSTALL_CONFIG  OFF CACHE BOOL "" FORCE)
set(ALSOFT_INSTALL_HRTF_DATA  OFF CACHE BOOL "" FORCE)
set(ALSOFT_INSTALL_AMBDEC_PRESETS  OFF CACHE BOOL "" FORCE)
set(ALSOFT_INSTALL_EXAMPLES  OFF CACHE BOOL "" FORCE)
set(ALSOFT_INSTALL_UTILS  OFF CACHE BOOL "" FORCE)
set(ALSOFT_UPDATE_BUILD_VERSION  OFF CACHE BOOL "" FORCE)

add_subdirectory(openal-soft)

# STB BUILD
set(STB_SRC
        stb/src/stb_image.cpp
        stb/src/stb_perlin.cpp
        )

add_library(stb STATIC ${STB_SRC})
target_include_directories(stb PUBLIC stb/include)