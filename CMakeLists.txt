cmake_minimum_required(VERSION 3.28)
project(
    atom.engine
    VERSION 0.1.0
    LANGUAGES CXX C)

cmake_policy(SET CMP0155 NEW)

find_package(atom_core REQUIRED)
find_package(atom_logging REQUIRED)

set(_CMAKE_WARN_DEPRECATED_TMP ${CMAKE_WARN_DEPRECATED})
set(CMAKE_WARN_DEPRECATED OFF)

# glm has cmake_minimum_required(VERSION 3.2) which triggers a deprecation warning.
find_package(glm REQUIRED)

set(CMAKE_WARN_DEPRECATED ${_CMAKE_WARN_DEPRECATED_TMP})

find_package(EnTT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(box2d REQUIRED)

# --------------------------------------------------------------------------------------------------
# glad
# --------------------------------------------------------------------------------------------------
add_subdirectory("vendor/glad")

# --------------------------------------------------------------------------------------------------
# stb
# --------------------------------------------------------------------------------------------------
add_subdirectory("vendor/stb")

# --------------------------------------------------------------------------------------------------
# imgui
# --------------------------------------------------------------------------------------------------
set(imgui_DIR $ENV{imgui_DIR})

add_library(imgui STATIC)
file(GLOB imgui_sources "${imgui_DIR}/*.cpp")
list(APPEND imgui_sources "${imgui_DIR}/backends/imgui_impl_opengl3.cpp"
     "${imgui_DIR}/backends/imgui_impl_glfw.cpp")
target_sources(imgui PRIVATE "${imgui_sources}")
target_include_directories(imgui PUBLIC "${imgui_DIR}")
target_link_libraries(imgui PUBLIC glfw)
target_compile_definitions(imgui PUBLIC "GLFW_INCLUDE_NONE")

# --------------------------------------------------------------------------------------------------
# atom.engine
# --------------------------------------------------------------------------------------------------

add_library(atom.engine STATIC)

file(GLOB_RECURSE modules "source/*.cppm")
file(GLOB_RECURSE sources "source/*.cpp")
target_sources(atom.engine PUBLIC FILE_SET CXX_MODULES FILES "${modules}")
target_sources(atom.engine PRIVATE "${sources}")
target_link_libraries(
    atom.engine
    PRIVATE atom::atom.core
            atom::atom.logging
            glm::glm
            glfw
            glad
            imgui
            stb
            EnTT::EnTT
            box2d::box2d)
target_compile_definitions(atom.engine PUBLIC "GLFW_INCLUDE_NONE")
target_compile_features(atom.engine PUBLIC "cxx_std_23")

# --------------------------------------------------------------------------------------------------
# atom.engine.sandbox
# --------------------------------------------------------------------------------------------------

add_executable(atom.engine.sandbox)

file(GLOB_RECURSE sandbox_modules "sandbox/*.cppm")
file(GLOB_RECURSE sandbox_sources "sandbox/*.cpp")
target_sources(
    atom.engine.sandbox
    PRIVATE FILE_SET CXX_MODULES FILES ${sandbox_modules}
    PRIVATE ${sandbox_sources})
target_link_libraries(atom.engine.sandbox PRIVATE atom.engine)

# --------------------------------------------------------------------------------------------------
# install phase
# --------------------------------------------------------------------------------------------------

install(
    TARGETS atom.engine imgui stb glad
    EXPORT atom_engine-targets
    FILE_SET CXX_MODULES
    DESTINATION "lib")

install(DIRECTORY "vendor/glad/include/" DESTINATION "include/")

install(
    EXPORT atom_engine-targets
    DESTINATION "cmake"
    FILE "atom_engine-targets.cmake"
    NAMESPACE "atom::")

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "atom_engine-config-version.cmake"
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(FILES "cmake/atom_engine-config.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/atom_engine-config-version.cmake" DESTINATION "cmake/")
