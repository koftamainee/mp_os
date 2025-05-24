cmake_minimum_required(VERSION 3.21)
project(mp_os)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add_compile_options(-std=c++20)

add_subdirectory(allocator)
add_subdirectory(arithmetic)
add_subdirectory(associative_container)
add_subdirectory(common)
add_subdirectory(logger)
