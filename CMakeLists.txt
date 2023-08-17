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

# Validation Test
add_executable(cesu8_validation_test src/test/test_main.cpp src/cesu8_scalar.cpp src/cesu8_SSE.cpp src/cesu8_AVX2.cpp src/cesu8_AVX512.cpp)
target_compile_options(cesu8_validation_test PRIVATE -std=c++17 -O0 -g -march=native)

target_link_libraries(
  cesu8_validation_test
  GTest::gtest_main
)

# Benchmark Scalar
add_executable(cesu8_benchmark_scalar src/benchmark/benchmark_scalar.cpp src/cesu8_scalar.cpp)
target_compile_options(cesu8_benchmark_scalar PRIVATE -std=c++17 -O3)

target_link_libraries(
  cesu8_benchmark_scalar
  benchmark::benchmark
)

# Benchmark SSE
add_executable(cesu8_benchmark_sse src/benchmark/benchmark_SSE.cpp src/cesu8_SSE.cpp src/cesu8_scalar.cpp)
target_compile_options(cesu8_benchmark_sse PRIVATE -std=c++17 -O3 -msse4.2)

target_link_libraries(
  cesu8_benchmark_sse
  benchmark::benchmark
)

# Benchmark AVX2
add_executable(cesu8_benchmark_avx2 src/benchmark/benchmark_AVX2.cpp src/cesu8_AVX2.cpp src/cesu8_scalar.cpp)
target_compile_options(cesu8_benchmark_avx2 PRIVATE -std=c++17 -O3 -mavx2)

target_link_libraries(
  cesu8_benchmark_avx2
  benchmark::benchmark
)

# Benchmark AVX512
#add_executable(cesu8_benchmark_avx512 src/benchmark/benchmark_AVX512.cpp src/cesu8_AVX512.cpp src/cesu8_scalar.cpp)
#target_compile_options(cesu8_benchmark_avx512 PRIVATE -std=c++17 -O3 -mavx2)

#target_link_libraries(
#  cesu8_benchmark_avx512
#  benchmark::benchmark
#)

# Collect Stats Executable
add_executable(collect_cesu8_stats src/tools/cesu8_stats.cpp src/cesu8_scalar.cpp)
target_compile_options(collect_cesu8_stats PRIVATE -std=c++17 -g -O0)

target_link_libraries(
  collect_cesu8_stats
  GTest::gtest_main
)

# Convert utf8 to cesu8 executable
add_executable(utf8_to_cesu8 src/tools/utf8_to_cesu8.cpp src/cesu8_scalar.cpp)
target_compile_options(utf8_to_cesu8 PRIVATE -std=c++17 -g -O0)

target_link_libraries(
  utf8_to_cesu8
  GTest::gtest_main
)


include(GoogleTest)
gtest_discover_tests(cesu8_validation_test)