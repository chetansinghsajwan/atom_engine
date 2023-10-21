cmake_minimum_required(VERSION 3.5)
project(AtomEngine VERSION 0.1.0 LANGUAGES CXX C)

include(CMake/CPM.cmake)
set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/Build/CPMCache")

CPMAddPackage("gh:shifu-dev/Atom.Core#dev")
CPMAddPackage("gh:shifu-dev/Atom.Logging#dev")
CPMAddPackage("gh:glfw/glfw#3.3.8")

# --------------------------------------------------------------------------------------------------
# C++20 Global Config
# --------------------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD "23")
set(CMAKE_CXX_STANDARD_REQUIRED "ON")
enable_testing()

# --------------------------------------------------------------------------------------------------
# Atom.Engine
# --------------------------------------------------------------------------------------------------

file(GLOB_RECURSE SOURCES "Source/Private/**.cpp"
    "Source/Private/**.h" "Public/**.h")

add_library(Atom.Engine STATIC ${SOURCES})
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