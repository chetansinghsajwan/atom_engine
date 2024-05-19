add_library(glad STATIC "source/glad.c")
target_include_directories(glad PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
