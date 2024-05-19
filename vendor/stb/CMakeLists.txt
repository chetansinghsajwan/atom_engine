add_library(stb STATIC)

file(GLOB_RECURSE stb_sources "sources/*.cpp")

target_sources(stb PRIVATE ${stb_sources})
target_include_directories(stb PUBLIC $ENV{stb_include_dir})
