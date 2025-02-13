add_library(stb STATIC)

set(stb_source $ENV{STB_SOURCE})
file(GLOB_RECURSE stb_sources "sources/*.cpp")

target_sources(stb PRIVATE ${stb_sources})
target_include_directories(stb PUBLIC ${stb_source})
