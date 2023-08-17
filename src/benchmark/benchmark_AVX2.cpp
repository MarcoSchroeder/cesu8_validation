#include <benchmark/benchmark.h>

#include "../cesu8.hpp"
#include "../tools/common.hpp"
#include "benchmark_common.hpp"

static void BM_ascii_data_small(benchmark::State& state)
{
    int index = state.range(0);
    int len   = state.range(1);

    std::string const& filepath = ASCII_SMALL_FILEPATHS[index];
    std::vector<char>  data     = read_file_as_binary(filepath);
    for (auto _ : state) {
        for (size_t i = 0; i < ITERATIONS_SMALL; ++i) {
            cesu8::is_valid_cesu8_AVX2((byte const*)data.data(), len);
        }
    }

    state.SetItemsProcessed(
        int64_t(state.iterations()) * int64_t(len) * ITERATIONS_SMALL);
}

BENCHMARK(BM_ascii_data_small)
    ->Args({0, 64})
    ->Args({1, 128})
    ->Args({2, 256})
    ->Args({3, 512})
    ->Args({4, 1024})
    ->Unit(benchmark::kMicrosecond);

static void BM_ascii_data(benchmark::State& state)
{
    int index = state.range(0);
    int len   = state.range(1);

    std::string const& filepath = ASCII_FILEPATHS[index];
    std::vector<char>  data     = read_file_as_binary(filepath);
    for (auto _ : state) {
        for (size_t i = 0; i < ITERATIONS; ++i) {
            cesu8::is_valid_cesu8_AVX2((byte const*)data.data(), len);
        }
    }

    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(len) * ITERATIONS);
}

BENCHMARK(BM_ascii_data)
    ->Args({0, 2048})
    ->Args({1, 4096})
    ->Args({2, 8192})
    ->Args({3, 16384})
    ->Args({4, 32768})
    ->Args({5, 65536})
    ->Args({6, 131072})
    ->Args({7, 262144})
    ->Args({8, 524288})
    ->Args({9, 1048576})
    ->Args({10, 2097152})
    ->Args({11, 4194304})
    ->Unit(benchmark::kMicrosecond);

static void BM_hangul_data_small(benchmark::State& state)
{
    int index = state.range(0);
    int len   = state.range(1);

    std::string const& filepath = HANGUL_SMALL_FILEPATHS[index];
    std::vector<char>  data     = read_file_as_binary(filepath);
    for (auto _ : state) {
        for (size_t i = 0; i < ITERATIONS_SMALL; ++i) {
            cesu8::is_valid_cesu8_AVX2((byte const*)data.data(), len);
        }
    }

    state.SetItemsProcessed(
        int64_t(state.iterations()) * int64_t(len) * ITERATIONS_SMALL);
}

BENCHMARK(BM_hangul_data_small)
    ->Args({0, 64})
    ->Args({1, 128})
    ->Args({2, 256})
    ->Args({3, 512})
    ->Args({4, 1024})
    ->Unit(benchmark::kMicrosecond);

static void BM_hangul_data(benchmark::State& state)
{
    int index = state.range(0);
    int len   = state.range(1);

    std::string const& filepath = HANGUL_FILEPATHS[index];
    std::vector<char>  data     = read_file_as_binary(filepath);
    for (auto _ : state) {
        for (size_t i = 0; i < ITERATIONS; ++i) {
            cesu8::is_valid_cesu8_AVX2((byte const*)data.data(), len);
        }
    }

    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(len) * ITERATIONS);
}

BENCHMARK(BM_hangul_data)
    ->Args({0, 2048})
    ->Args({1, 4096})
    ->Args({2, 8192})
    ->Args({3, 16384})
    ->Args({4, 32768})
    ->Args({5, 65536})
    ->Args({6, 131072})
    ->Args({7, 262144})
    ->Args({8, 524288})
    ->Args({9, 1048576})
    ->Args({10, 2097152})
    ->Args({11, 4194304})
    ->Unit(benchmark::kMicrosecond);

static void BM_random_data_small(benchmark::State& state)
{
    int index = state.range(0);
    int len   = state.range(1);

    std::string const& filepath = RANDOM_SMALL_FILEPATHS[index];
    std::vector<char>  data     = read_file_as_binary(filepath);
    for (auto _ : state) {
        for (size_t i = 0; i < ITERATIONS_SMALL; ++i) {
            cesu8::is_valid_cesu8_AVX2((byte const*)data.data(), len);
        }
    }

    state.SetItemsProcessed(
        int64_t(state.iterations()) * int64_t(len) * ITERATIONS_SMALL);
}

BENCHMARK(BM_random_data_small)
    ->Args({0, 64})
    ->Args({1, 128})
    ->Args({2, 256})
    ->Args({3, 512})
    ->Args({4, 1024})
    ->Unit(benchmark::kMicrosecond);

static void BM_random_data(benchmark::State& state)
{
    int index = state.range(0);
    int len   = state.range(1);

    std::string const& filepath = HANGUL_FILEPATHS[index];
    std::vector<char>  data     = read_file_as_binary(filepath);
    for (auto _ : state) {
        for (size_t i = 0; i < ITERATIONS; ++i) {
            cesu8::is_valid_cesu8_AVX2((byte const*)data.data(), len);
        }
    }

    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(len) * ITERATIONS);
}

BENCHMARK(BM_random_data)
    ->Args({0, 2048})
    ->Args({1, 4096})
    ->Args({2, 8192})
    ->Args({3, 16384})
    ->Args({4, 32768})
    ->Args({5, 65536})
    ->Args({6, 131072})
    ->Args({7, 262144})
    ->Args({8, 524288})
    ->Args({9, 1048576})
    ->Args({10, 2097152})
    ->Args({11, 4194304})
    ->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
