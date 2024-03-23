cmake_minimum_required(VERSION 3.5)
project(
    atom.engine
    VERSION 0.1.0
    LANGUAGES CXX C)

include(FetchContent)
set(FETCHCONTENT_QUIET "OFF")

FetchContent_Declare(
    atom_core
    GIT_REPOSITORY "https://github.com/shifu-dev/atom.core.git"
    GIT_TAG "dev"
    GIT_SHALLOW true
    EXCLUDE_FROM_ALL)

FetchContent_Declare(
    atom_logging
    GIT_REPOSITORY "https://github.com/shifu-dev/atom.logging.git"
    GIT_TAG "dev"
    GIT_SHALLOW true
    EXCLUDE_FROM_ALL)

FetchContent_Declare(
    glm
    GIT_REPOSITORY "https://github.com/g-truc/glm.git"
    GIT_TAG "1.0.1"
    GIT_SHALLOW true
    EXCLUDE_FROM_ALL)

FetchContent_Declare(
    glfw3
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.3.9"
    GIT_SHALLOW true
    EXCLUDE_FROM_ALL FIND_PACKAGE_ARGS "")

FetchContent_Declare(
    imgui
    GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
    GIT_TAG "docking"
    GIT_SHALLOW true
    EXCLUDE_FROM_ALL)

FetchContent_MakeAvailable(atom_core atom_logging glm glfw3 imgui)
FetchContent_GetProperties(imgui)

# --------------------------------------------------------------------------------------------------
# glad
# --------------------------------------------------------------------------------------------------
add_subdirectory("vendor/glad")

# --------------------------------------------------------------------------------------------------
# stb_image
# --------------------------------------------------------------------------------------------------
add_subdirectory("vendor/stb_image")

# --------------------------------------------------------------------------------------------------
# imgui
# --------------------------------------------------------------------------------------------------
add_library(imgui STATIC)
file(GLOB imgui_sources "${imgui_SOURCE_DIR}/*.cpp")
list(APPEND imgui_sources "${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
     "${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp")
target_sources(imgui PRIVATE "${imgui_sources}")
target_include_directories(imgui PUBLIC "${imgui_SOURCE_DIR}")
target_link_libraries(imgui PUBLIC glfw)
target_compile_definitions(imgui PRIVATE "GLFW_INCLUDE_NONE")

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

file(GLOB_RECURSE sources "source/*.cpp")
target_sources(atom.engine PRIVATE "${sources}")
target_include_directories(atom.engine PUBLIC "include")
target_include_directories(atom.engine PUBLIC "source")
target_link_libraries(atom.engine PUBLIC atom.core)
target_link_libraries(atom.engine PUBLIC atom.logging)
target_link_libraries(atom.engine PUBLIC glm)
target_link_libraries(atom.engine PUBLIC glfw)
target_link_libraries(atom.engine PUBLIC glad)
target_link_libraries(atom.engine PUBLIC imgui)
target_link_libraries(atom.engine PUBLIC stb_image)
target_compile_definitions(atom.engine PUBLIC "GLFW_INCLUDE_NONE")

# --------------------------------------------------------------------------------------------------
# atom.engine.sandbox
# --------------------------------------------------------------------------------------------------

add_executable(atom.engine.sandbox)
target_sources(atom.engine.sandbox PRIVATE "sandbox/sandbox.cpp" "sandbox/sandbox_layer.cpp")
target_link_libraries(atom.engine.sandbox PRIVATE atom.engine)
