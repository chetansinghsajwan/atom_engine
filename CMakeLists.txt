cmake_minimum_required(VERSION 3.5)
project(AtomEngine VERSION 0.1.0 LANGUAGES CXX C)

include(FetchContent)

FetchContent_Declare(
    atom_core
    GIT_REPOSITORY "https://github.com/shifu-dev/atom.core.git"
    GIT_TAG        "dev"
    GIT_SHALLOW    true
)

FetchContent_Declare(
    atom_logging
    GIT_REPOSITORY "https://github.com/shifu-dev/atom.logging.git"
    GIT_TAG        "dev"
    GIT_SHALLOW    true
)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG        "3.3.9"
    GIT_SHALLOW    true
)

FetchContent_MakeAvailable(atom_core atom_logging glfw)
FetchContent_GetProperties(atom_core)

add_subdirectory("vendor/glad")

include("${atom_core_SOURCE_DIR}/cmake/enable_modules.cmake")

# --------------------------------------------------------------------------------------------------
# C++20 Global Config
# --------------------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD "23")
set(CMAKE_CXX_STANDARD_REQUIRED "ON")
enable_testing()

# --------------------------------------------------------------------------------------------------
# Atom.Engine
# --------------------------------------------------------------------------------------------------

file(GLOB_RECURSE sources "src/*.cpp")

add_library(atom.engine STATIC)
target_sources(atom.engine PUBLIC
    FILE_SET modules TYPE CXX_MODULES FILES
    "${sources}"
)

target_link_libraries(atom.engine PRIVATE atom.core)
target_link_libraries(atom.engine PRIVATE atom.logging)
target_link_libraries(atom.engine PRIVATE glfw)
target_link_libraries(atom.engine PRIVATE glad)
target_compile_definitions(atom.engine PRIVATE "GLFW_INCLUDE_NONE")

# --------------------------------------------------------------------------------------------------
# Atom.Engine.Sandbox
# --------------------------------------------------------------------------------------------------

add_executable(atom.engine.sandbox "sandbox/sandbox.cpp")
target_link_libraries(atom.engine.sandbox PRIVATE atom.engine)
