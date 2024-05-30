include(CMakeFindDependencyMacro)

# glm has cmake_minimum_required(VERSION 3.2) which triggers a deprecation warning.
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

find_dependency("atom_core" REQUIRED)
find_dependency("atom_logging" REQUIRED)
find_dependency("EnTT" REQUIRED)
find_dependency("glfw3" REQUIRED)
find_dependency("box2d" REQUIRED)
find_dependency("glm" REQUIRED)
find_dependency("glslang" REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/atom_engine-targets.cmake")
