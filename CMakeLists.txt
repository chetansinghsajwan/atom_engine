cmake_minimum_required(VERSION 3.28)
project("atom_engine" VERSION "0.1.0")
enable_language(CXX)

cmake_policy(SET CMP0155 NEW)

# --------------------------------------------------------------------------------------------------
# options
# --------------------------------------------------------------------------------------------------
option(atom_core_build_docs "Enable this to build docs." OFF)

# --------------------------------------------------------------------------------------------------
# atom_engine
# --------------------------------------------------------------------------------------------------

# glm has cmake_minimum_required(VERSION 3.2) which triggers a deprecation warning.
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

find_package("atom_core" REQUIRED)
find_package("atom_logging" REQUIRED)
find_package("glm" REQUIRED)
find_package("EnTT" REQUIRED)
find_package("glfw3" REQUIRED)
find_package("imgui" REQUIRED)
find_package("box2d" REQUIRED)
find_package("msdf-atlas-gen" REQUIRED)
find_package("glslang" REQUIRED)

add_subdirectory("vendor/glad")
add_subdirectory("vendor/stb")

if(NOT DEFINED ATOM_ENGINE_ASSETS_DIR)
    set(ATOM_ENGINE_ASSETS_DIR "${CMAKE_CURRENT_LIST_DIR}/assets")
endif()
configure_file("include/config.h.in" "include/config.h")

add_library(atom_engine STATIC)

file(GLOB_RECURSE atom_engine_modules "source/*.cppm" "source/*.cxx")
file(GLOB_RECURSE atom_engine_sources "source/*.cpp")
target_sources(
    atom_engine
    PUBLIC FILE_SET CXX_MODULES FILES "${atom_engine_modules}"
    PRIVATE "${atom_engine_sources}")

target_link_libraries(
    atom_engine
    PUBLIC
        "atom_core"
        "atom_logging"
    PRIVATE
        "glfw"
        "glad"
        "stb"
        "glm::glm"
        "imgui::imgui"
        "EnTT::EnTT"
        "box2d::box2d"
        "msdfgen::msdfgen"
        "msdf-atlas-gen::msdf-atlas-gen"
        "glslang::glslang"
        "glslang::glslang-default-resource-limits"
        "glslang::OSDependent"
        "glslang::MachineIndependent"
        "glslang::GenericCodeGen"
        "glslang::SPVRemapper"
        "glslang::SPIRV")

target_compile_definitions(atom_engine PUBLIC "GLFW_INCLUDE_NONE")
target_compile_features(atom_engine PUBLIC "cxx_std_23")
target_include_directories(atom_engine
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>)

# --------------------------------------------------------------------------------------------------
# sandbox
# --------------------------------------------------------------------------------------------------

add_executable(atom_engine_sandbox)

file(GLOB_RECURSE atom_engine_sandbox_modules "sandbox/*.cppm" "sandbox/*.cxx")
file(GLOB_RECURSE atom_engine_sandbox_sources "sandbox/*.cpp")
target_sources(
    atom_engine_sandbox
    PRIVATE FILE_SET CXX_MODULES FILES "${atom_engine_sandbox_modules}"
    PRIVATE "${atom_engine_sandbox_sources}")
target_link_libraries(atom_engine_sandbox PRIVATE "atom_engine")

# --------------------------------------------------------------------------------------------------
# docs
# --------------------------------------------------------------------------------------------------

if(atom_engine_build_docs)
    find_package("Doxygen" REQUIRED)

    doxygen_add_docs(atom_engine_docs
        "${atom_engine_modules}" "${atom_engine_sources}"
        CONFIG_FILE "${CMAKE_CURRENT_LIST_DIR}/Doxyfile"
        USE_STAMP_FILE)
endif()

# --------------------------------------------------------------------------------------------------
# install
# --------------------------------------------------------------------------------------------------

install(
    TARGETS "atom_engine" "stb" "glad"
    EXPORT atom_engine-targets
    FILE_SET CXX_MODULES
    DESTINATION "lib"
    INCLUDES DESTINATION "include/")

install(
    EXPORT atom_engine-targets
    DESTINATION "cmake"
    FILE "atom_engine-targets.cmake"
    NAMESPACE "atom::")

install(DIRECTORY "vendor/glad/include/" DESTINATION "include/")
install(DIRECTORY "assets/" DESTINATION "assets/")

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "atom_engine-config-version.cmake"
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(FILES "cmake/atom_engine-config.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/atom_engine-config-version.cmake" DESTINATION "cmake/")
