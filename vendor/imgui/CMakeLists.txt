add_library(imgui STATIC)
add_library(imgui::imgui ALIAS imgui)

set(imgui_source $ENV{IMGUI_SOURCE})

file(GLOB imgui_sources "${imgui_source}/*.cpp")
list(APPEND imgui_sources "${imgui_source}/backends/imgui_impl_glfw.cpp"
     "${imgui_source}/backends/imgui_impl_opengl3.cpp")

target_sources(imgui PRIVATE ${imgui_sources})
target_include_directories(imgui PUBLIC ${imgui_source})
