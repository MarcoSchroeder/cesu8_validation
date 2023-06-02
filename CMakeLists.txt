cmake_minimum_required(VERSION 3.14)
project(cesu8_validation)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest googlebenchmark)


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

add_executable(cesu8_benchmark_sse src/benchmark/benchmark_SSE.cpp src/cesu8_SSE.cpp src/cesu8_scalar.cpp)
target_compile_options(cesu8_benchmark_sse PRIVATE -std=c++17 -O3 -msse4.2)

target_link_libraries(
  cesu8_benchmark_sse 
  benchmark::benchmark
)

add_executable(cesu8_benchmark_avx src/benchmark/benchmark_AVX.cpp src/cesu8_AVX.cpp src/cesu8_scalar.cpp)
target_compile_options(cesu8_benchmark_avx PRIVATE -std=c++17 -O3 -mavx2)

target_link_libraries(
  cesu8_benchmark_avx 
  benchmark::benchmark
)

include(GoogleTest)
gtest_discover_tests(cesu8_validation_test_scalar)