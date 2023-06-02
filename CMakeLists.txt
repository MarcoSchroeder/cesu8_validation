cmake_minimum_required(VERSION 3.14)
project(cesu8_validation)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_Declare(
  googlebenchmark
  URL https://github.com/google/benchmark/archive/v1.5.2.tar.gz
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest googlebenchmark)

set(CMAKE_BUILD_TYPE Release)

# Tests
project(cesu8_validation)
enable_testing()

add_executable(cesu8_validation_test_scalar src/test/test_scalar.cpp src/cesu8_scalar.cpp)
target_compile_options(cesu8_validation_test_scalar PRIVATE -std=c++17 -O2)

target_link_libraries(
  cesu8_validation_test_scalar
  GTest::gtest_main
)

add_executable(cesu8_validation_test_sse src/test/test_SSE.cpp src/cesu8_SSE.cpp src/cesu8_scalar.cpp)
target_compile_options(cesu8_validation_test_sse PRIVATE -std=c++17 -O2 -msse4.2)

target_link_libraries(
  cesu8_validation_test_sse
  GTest::gtest_main
)

add_executable(cesu8_validation_test_avx src/test/test_AVX.cpp src/cesu8_AVX.cpp src/cesu8_scalar.cpp)
target_compile_options(cesu8_validation_test_avx PRIVATE -std=c++17 -O2 -mavx2)

target_link_libraries(
  cesu8_validation_test_avx
  GTest::gtest_main
)

add_executable(cesu8_benchmark_scalar src/benchmark/benchmark_scalar.cpp src/cesu8_scalar.cpp)
target_compile_options(cesu8_benchmark_scalar PRIVATE -std=c++17 -O3)

target_link_libraries(
  cesu8_benchmark_scalar 
  benchmark::benchmark
)

include(GoogleTest)
gtest_discover_tests(cesu8_validation_test_scalar)