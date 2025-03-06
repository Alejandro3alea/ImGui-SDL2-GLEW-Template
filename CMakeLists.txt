cmake_minimum_required(VERSION 3.10)

set(TARGET_NAME ImGuiTemplate)
file(GLOB_RECURSE ALL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

project(${TARGET_NAME})

add_executable(${TARGET_NAME} ${ALL_SOURCES})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})


set(THIRD_PARTY_LIBRARIES "third-party")
set(IMGUI_INCLUDE_DIRS "${THIRD_PARTY_LIBRARIES}/imgui")
set(FREETYPE_INCLUDE_DIRS "${THIRD_PARTY_LIBRARIES}/freetype")
target_include_directories(${TARGET_NAME} 
    PRIVATE 
        ${FREETYPE_INCLUDE_DIRS}
        ${IMGUI_INCLUDE_DIRS}
    )

target_link_directories(${TARGET_NAME} PRIVATE /usr/lib)
target_link_libraries(${TARGET_NAME} PRIVATE ${GLEW_LIBRARIES} SDL2 freetype)