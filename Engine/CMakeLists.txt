cmake_minimum_required(VERSION 3.17)

project(Engine LANGUAGES C CXX)

file(GLOB_RECURSE BWAT_ENGINE_SRC
        *.cpp)
file(GLOB_RECURSE BWAT_ENGINE_HEADERS
        *.hpp)

set(ENGINE_LIBRARIES glad glfw assimp flatbuffers imgui OpenAL stb json dirent AudioFile lua sol2
        PhysXExtensions PhysX PhysXPvdSDK PhysXVehicle PhysXCharacterKinematic PhysXCooking PhysXCommon PhysXFoundation)

add_library(Engine STATIC ${BWAT_ENGINE_SRC} ${BWAT_ENGINE_HEADERS})
target_include_directories(Engine PUBLIC include)
target_link_libraries(Engine PUBLIC ${ENGINE_LIBRARIES})

