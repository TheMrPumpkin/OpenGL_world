cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0072 NEW)
project(OpenGL-project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

find_path(GLM_INCLUDE_DIR glm/glm.hpp
    HINTS ${CMAKE_SOURCE_DIR}/include/glm
    REQUIRED)

# --- Integrate Assimp via FetchContent ---
include(FetchContent)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG        v5.4.3
)
FetchContent_MakeAvailable(assimp)

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
    assimp
    dl
)

file(COPY ${CMAKE_SOURCE_DIR}/images
     DESTINATION ${CMAKE_BINARY_DIR})