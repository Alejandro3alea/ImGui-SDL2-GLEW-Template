cmake_minimum_required(VERSION 3.10)

set(TARGET_NAME ImGuiTemplate)
file(GLOB_RECURSE ALL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

project(${TARGET_NAME})

add_executable(${TARGET_NAME} ${ALL_SOURCES})

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

message(${GLEW_LIBRARIES})
message(${GLEW_LIBRARIES})
message(${GLEW_LIBRARIES})

set(THIRD_PARTY_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/third-party")
set(IMGUI_INCLUDE_DIRS "${THIRD_PARTY_LIBRARIES}/imgui")
set(FREETYPE_INCLUDE_DIRS "${THIRD_PARTY_LIBRARIES}/freetype")
target_include_directories(${TARGET_NAME} 
    PRIVATE 
        ${THIRD_PARTY_LIBRARIES}
        ${GLEW_INCLUDE_DIRS}
        ${FREETYPE_INCLUDE_DIRS}
        ${IMGUI_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

target_link_directories(${TARGET_NAME} PRIVATE /usr/lib)
target_link_libraries(${TARGET_NAME} 
    PRIVATE 
        ${GLEW_LIBRARIES}
        SDL2
        freetype
        ${OPENGL_gl_LIBRARY}
    )