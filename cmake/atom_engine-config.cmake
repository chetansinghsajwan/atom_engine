include(CMakeFindDependencyMacro)

find_dependency(atom_core REQUIRED)
find_dependency(atom_logging REQUIRED)
find_dependency(EnTT REQUIRED)
find_dependency(glfw3 REQUIRED)
find_dependency(box2d REQUIRED)

set(_CMAKE_WARN_DEPRECATED_TMP ${CMAKE_WARN_DEPRECATED})
set(CMAKE_WARN_DEPRECATED OFF)

# glm has cmake_minimum_required(VERSION 3.2) which triggers a deprecation warning.
find_dependency(glm REQUIRED)

set(CMAKE_WARN_DEPRECATED ${_CMAKE_WARN_DEPRECATED_TMP})

include("${CMAKE_CURRENT_LIST_DIR}/atom_engine-targets.cmake")
