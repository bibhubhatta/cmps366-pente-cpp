cmake_minimum_required(VERSION 3.25.2)
project(pente)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
