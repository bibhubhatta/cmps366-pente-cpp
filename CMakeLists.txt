cmake_minimum_required(VERSION 3.25.2)
project(pente)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Boiler plate from https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test if testing framework is working
add_executable(
        tests
        tests/testing_framework_test.cpp
)

target_link_libraries(
        tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)