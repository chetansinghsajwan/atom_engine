cmake_minimum_required(VERSION 3.28)
project(
    atom.engine
    VERSION 0.1.0
    LANGUAGES CXX C)

cmake_policy(SET CMP0155 NEW)

include(FetchContent)
set(FETCHCONTENT_QUIET "ON")

set(CMAKE_CXX_STANDARD "23")
set(CMAKE_CXX_STANDARD_REQUIRED "ON")
enable_testing()

FetchContent_Declare(
    atom_core
    GIT_REPOSITORY "https://github.com/shifu-dev/atom.core.git"
    GIT_TAG "main"
    GIT_SHALLOW true
    EXCLUDE_FROM_ALL)

FetchContent_Declare(
    atom_logging
    GIT_REPOSITORY "https://github.com/shifu-dev/atom.logging.git"
    GIT_TAG "main"
    GIT_SHALLOW true
    EXCLUDE_FROM_ALL)

FetchContent_Declare(
    glm
    GIT_REPOSITORY "https://github.com/g-truc/glm.git"
    GIT_TAG "1.0.1"
    GIT_SHALLOW true
    EXCLUDE_FROM_ALL)

# FetchContent_Declare( glfw3 GIT_REPOSITORY "https://github.com/glfw/glfw.git" GIT_TAG "3.3.9"
# GIT_SHALLOW true EXCLUDE_FROM_ALL FIND_PACKAGE_ARGS "")

FetchContent_Declare(
    imgui
    GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
    GIT_TAG "docking"
    GIT_SHALLOW true
    EXCLUDE_FROM_ALL)

FetchContent_Declare(
    entt
    GIT_REPOSITORY "https://github.com/skypjack/entt.git"
    GIT_TAG "v3.13.2"
    GIT_SHALLOW true
    EXCLUDE_FROM_ALL)

FetchContent_MakeAvailable(atom_core atom_logging glm imgui entt)
FetchContent_GetProperties(imgui)

find_package(glfw3 CONFIG REQUIRED)
get_target_property(GLFW_INCLUDE_DIR glfw INTERFACE_INCLUDE_DIRECTORIES)

# --------------------------------------------------------------------------------------------------
# glad
# --------------------------------------------------------------------------------------------------
add_subdirectory("vendor/glad")

# --------------------------------------------------------------------------------------------------
# stb_image
# --------------------------------------------------------------------------------------------------
add_subdirectory("vendor/stb_image")

# temporary fix for clang-scan-dep not finding std headers in nix.
target_compile_options(
    stb_image
    PUBLIC "-I/nix/store/p0siwwr4pfh6d9026ygvagvp43gyck69-libcxx-18.1.3-dev/include/c++/v1"
           "-I/nix/store/ij144ma6vs8acil8r9hgr8xkb1dp9azg-glibc-2.39-5-dev/include"
           "-I${GLFW_INCLUDE_DIR}")

# --------------------------------------------------------------------------------------------------
# imgui
# --------------------------------------------------------------------------------------------------
add_library(imgui STATIC)
file(GLOB imgui_sources "${imgui_SOURCE_DIR}/*.cpp")
list(APPEND imgui_sources "${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
     "${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp")
target_sources(imgui PUBLIC "${imgui_sources}")
target_include_directories(imgui PUBLIC "${imgui_SOURCE_DIR}")
target_link_libraries(imgui PUBLIC glfw)
target_compile_definitions(imgui PUBLIC "GLFW_INCLUDE_NONE")

# temporary fix for clang-scan-dep not finding std headers in nix.
target_compile_options(
    imgui
    PUBLIC "-I/nix/store/p0siwwr4pfh6d9026ygvagvp43gyck69-libcxx-18.1.3-dev/include/c++/v1"
           "-I/nix/store/ij144ma6vs8acil8r9hgr8xkb1dp9azg-glibc-2.39-5-dev/include"
           "-I${GLFW_INCLUDE_DIR}")

# --------------------------------------------------------------------------------------------------
# atom.engine
# --------------------------------------------------------------------------------------------------

add_library(atom.engine STATIC)

file(GLOB_RECURSE sources "source/*.cpp")
file(GLOB_RECURSE modules "source/*.cppm")
target_sources(atom.engine PUBLIC "${sources}")
target_sources(atom.engine PUBLIC FILE_SET CXX_MODULES FILES "${modules}")
target_link_libraries(
    atom.engine
    PUBLIC atom.core
           atom.logging
           glm
           glfw
           glad
           imgui
           stb_image
           EnTT::EnTT)
target_compile_definitions(atom.engine PUBLIC "GLFW_INCLUDE_NONE")

# temporary fix for clang-scan-dep not finding std headers in nix.
target_compile_options(
    atom.engine
    PUBLIC "-I/nix/store/p0siwwr4pfh6d9026ygvagvp43gyck69-libcxx-18.1.3-dev/include/c++/v1"
           "-I/nix/store/ij144ma6vs8acil8r9hgr8xkb1dp9azg-glibc-2.39-5-dev/include"
           "-I${GLFW_INCLUDE_DIR}")

# --------------------------------------------------------------------------------------------------
# atom.engine.sandbox
# --------------------------------------------------------------------------------------------------

add_executable(atom.engine.sandbox)

file(GLOB_RECURSE sandbox_modules "sandbox/*.cppm")
file(GLOB_RECURSE sandbox_sources "sandbox/*.cpp")
target_sources(atom.engine.sandbox PUBLIC FILE_SET CXX_MODULES FILES ${sandbox_modules})
target_sources(atom.engine.sandbox PUBLIC ${sandbox_sources})
target_link_libraries(atom.engine.sandbox PUBLIC atom.engine)
