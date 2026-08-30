cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0072 NEW)
project(OpenGL-project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

find_path(GLM_INCLUDE_DIR glm/glm.hpp
    HINTS ${CMAKE_SOURCE_DIR}/include/glm
    REQUIRED)

file(GLOB_RECURSE SOURCES
"src/*.cpp"
"src/*.c"
"src/*.h"
"include/glad/*.c"
)

add_executable(OpenGL-project ${SOURCES})

target_include_directories(OpenGL-project PRIVATE
    include
${GLM_INCLUDE_DIR}
)

target_link_libraries(OpenGL-project PRIVATE
    OpenGL::GL
    glfw
    dl
)

file(COPY ${CMAKE_SOURCE_DIR}/images
     DESTINATION ${CMAKE_BINARY_DIR})