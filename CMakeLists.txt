cmake_minimum_required(VERSION 3.5)
project(AtomEngine VERSION 0.1.0 LANGUAGES CXX C)

include(FetchContent)

FetchContent_Declare(
    atom-core
    GIT_REPOSITORY "https://github.com/shifu-dev/Atom.Core.git"
    GIT_TAG        "dev"
    GIT_SHALLOW    true
)

FetchContent_Declare(
    atom-logging
    GIT_REPOSITORY "https://github.com/shifu-dev/Atom.Logging.git"
    GIT_TAG        "dev"
    GIT_SHALLOW    true
)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG        "3.3.9"
    GIT_SHALLOW    true
)

FetchContent_MakeAvailable(atom-core atom-logging glfw)
FetchContent_GetProperties(atom-core)

include("${atom-core_SOURCE_DIR}/CMake/enable-modules.cmake")

# --------------------------------------------------------------------------------------------------
# C++20 Global Config
# --------------------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD "23")
set(CMAKE_CXX_STANDARD_REQUIRED "ON")
enable_testing()

# --------------------------------------------------------------------------------------------------
# Atom.Engine
# --------------------------------------------------------------------------------------------------

file(GLOB_RECURSE SOURCES "Source/Private/**.cpp")

add_library(Atom.Engine STATIC)
target_sources(Atom.Engine PUBLIC
    FILE_SET modules TYPE CXX_MODULES FILES
    "${SOURCES}"
)
target_include_directories(Atom.Engine PRIVATE "Source/Private/")
target_include_directories(Atom.Engine PUBLIC "Source/Public/")

target_compile_definitions(Atom.Engine PRIVATE ATOM_EXPORT)

target_link_libraries(Atom.Engine PUBLIC Atom.Core)
target_link_libraries(Atom.Engine PUBLIC Atom.Logging)
target_link_libraries(Atom.Engine PUBLIC glfw)

# --------------------------------------------------------------------------------------------------
# Atom.Engine.Sandbox
# --------------------------------------------------------------------------------------------------

add_executable(Atom.Engine.Sandbox "Source/Sandbox/Sandbox.cpp")
target_include_directories(Atom.Engine.Sandbox PRIVATE "Source/Sandbox")
target_link_libraries(Atom.Engine.Sandbox PUBLIC Atom.Engine)