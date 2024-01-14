cmake_minimum_required(VERSION 3.27)
project(Memory_Units)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)
enable_testing()

add_executable(memory_size_tests
        include
        tests/base2_constructors.cc
        tests/base10_constructors.cc
        tests/base2_arithmetic.cc
        tests/base10_arithmetic.cc
        tests/base2_literals.cc
        tests/base10_literals.cc
        tests/base2_relational.cc
        tests/base10_relational.cc
        tests/base2_memory_cast.cc
        tests/base10_memory_cast.cc
        tests/memory_size_tests.cc
)
target_link_libraries(memory_size_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(memory_size_tests)