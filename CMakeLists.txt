cmake_minimum_required(VERSION 3.5)
project(AtomEngine VERSION 0.1.0 LANGUAGES CXX C)

include("$env{ATOM_CORE}/CMakeLists.txt")
include("$env{ATOM_LOGGING}/CMakeLists.txt")
find_package(glfw3 REQUIRED)

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