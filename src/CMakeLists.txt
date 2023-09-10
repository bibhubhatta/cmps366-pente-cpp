cmake_minimum_required(VERSION 3.25.2)
project(pente_src)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
        pente_lib STATIC
        Serial.cpp Serial.h
        Board.cpp Board.h
        Position.cpp Position.h)

target_include_directories(pente_lib
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})