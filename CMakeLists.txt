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

add_executable(base10_constructors include tests/base10_constructors.cc)
target_link_libraries(base10_constructors GTest::gtest_main)
add_executable(base2_constructors include tests/base2_constructors.cc)
target_link_libraries(base2_constructors GTest::gtest_main)

add_executable(base2_arithmetic include tests/base2_arithmetic.cc)
target_link_libraries(base2_arithmetic GTest::gtest_main)
add_executable(base10_arithmetic include tests/base10_arithmetic.cc)
target_link_libraries(base10_arithmetic GTest::gtest_main)

add_executable(base2_literals include tests/base2_literals.cc)
target_link_libraries(base2_literals GTest::gtest_main)
add_executable(base10_literals include tests/base10_literals.cc)
target_link_libraries(base10_literals GTest::gtest_main)

add_executable(base2_relational include tests/base10_relational.cc)
target_link_libraries(base2_relational GTest::gtest_main)
add_executable(base10_relational include tests/base2_relational.cc)
target_link_libraries(base10_relational GTest::gtest_main)

add_executable(base10_memory_cast include tests/base10_memory_cast.cc)
target_link_libraries(base10_memory_cast GTest::gtest_main)
add_executable(base2_memory_cast include tests/base2_memory_cast.cc)
target_link_libraries(base2_memory_cast GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(base2_constructors
        base10_constructors
        base2_arithmetic
        base10_arithmetic
        base2_literals
        base10_literals,
        base2_relational,
        base10_relational,
        base2_memory_cast,
        base10_memory_cast)