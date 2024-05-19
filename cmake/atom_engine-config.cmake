include(CMakeFindDependencyMacro)

find_dependency(atom_core REQUIERD)
find_dependency(atom_logging REQUIERD)
find_dependency(glm REQUIERD)
find_dependency(imgui REQUIERD)
find_dependency(entt REQUIERD)
find_dependency(glfw3 REQUIERD)

include("atom_engine-targets.cmake")
