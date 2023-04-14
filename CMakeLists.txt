cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
project(ModLine VERSION 0.0.2)

set(LIBDSP_LIB_ONLY ON CACHE BOOL "Only build libdsp static lib" FORCE)

add_subdirectory(externals)
add_subdirectory(plugin)