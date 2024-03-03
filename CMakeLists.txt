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
    glm
    GIT_REPOSITORY "https://github.com/g-truc/glm.git"
    GIT_TAG        "1.0.1"
    GIT_SHALLOW    true
)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG        "3.3.9"
    GIT_SHALLOW    true
)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
    GIT_TAG        "docking"
    GIT_SHALLOW    true
)

FetchContent_MakeAvailable(atom_core atom_logging glm glfw imgui)
FetchContent_GetProperties(atom_core imgui)

# --------------------------------------------------------------------------------------------------
# glad
# --------------------------------------------------------------------------------------------------
add_subdirectory("vendor/glad")

# --------------------------------------------------------------------------------------------------
# imgui
# --------------------------------------------------------------------------------------------------
add_library(imgui SHARED)
file(GLOB imgui_sources "${imgui_SOURCE_DIR}/*.cpp")
list(APPEND imgui_sources
    "${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp")
target_sources(imgui PRIVATE "${imgui_sources}")
target_include_directories(imgui PUBLIC "${imgui_SOURCE_DIR}")
target_link_libraries(imgui PUBLIC glfw)
target_compile_definitions(imgui PRIVATE "GLFW_INCLUDE_NONE")

# --------------------------------------------------------------------------------------------------
# enable moduels
# --------------------------------------------------------------------------------------------------
include("${atom_core_SOURCE_DIR}/cmake/enable_modules.cmake")

# --------------------------------------------------------------------------------------------------
# cpp20 global configs
# --------------------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD "23")
set(CMAKE_CXX_STANDARD_REQUIRED "ON")
enable_testing()

# --------------------------------------------------------------------------------------------------
# atom.engine
# --------------------------------------------------------------------------------------------------

add_library(atom.engine STATIC)

file(GLOB_RECURSE sources "src/*.cpp")
target_sources(atom.engine PRIVATE "${sources}")
target_include_directories(atom.engine PUBLIC "include")
target_include_directories(atom.engine PRIVATE "src")
target_link_libraries(atom.engine PRIVATE atom.core)
target_link_libraries(atom.engine PRIVATE atom.logging)
target_link_libraries(atom.engine PRIVATE glm)
target_link_libraries(atom.engine PRIVATE glfw)
target_link_libraries(atom.engine PRIVATE glad)
target_link_libraries(atom.engine PRIVATE imgui)
target_compile_definitions(atom.engine PRIVATE "GLFW_INCLUDE_NONE")

# --------------------------------------------------------------------------------------------------
# atom.engine.sandbox
# --------------------------------------------------------------------------------------------------

add_executable(atom.engine.sandbox "sandbox/sandbox.cpp")
target_link_libraries(atom.engine.sandbox PRIVATE atom.engine)
