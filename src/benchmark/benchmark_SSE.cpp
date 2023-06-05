#include <benchmark/benchmark.h>

#include "../cesu8.hpp"
#include "benchmark_common.hpp"

static void BM_ascii_data_small(benchmark::State& state)
{
    byte* data = new byte[state.range(0)];
    set_ascii_data(data, state.range(0));
    for (auto _ : state) {
        for(size_t i=0; i<ITERATIONS_SMALL; ++i) {
            cesu8::is_valid_cesu8_SSE(data, state.range(0));
        }
    }
    delete [] data;

    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)) * ITERATIONS);
}

BENCHMARK(BM_ascii_data_small)->RangeMultiplier(2)->Range(SMALL_MIN, SMALL_MAX)->Unit(benchmark::kMicrosecond);

static void BM_ascii_data(benchmark::State& state)
{
    byte* data = new byte[state.range(0)];
    set_ascii_data(data, state.range(0));
    for (auto _ : state) {
        for(size_t i=0; i<ITERATIONS; ++i) {
            cesu8::is_valid_cesu8_SSE(data, state.range(0));
        }
    }
    delete [] data;

    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)) * ITERATIONS);
}

BENCHMARK(BM_ascii_data)->RangeMultiplier(2)->Range(BIG_MIN, BIG_MAX)->Unit(benchmark::kMicrosecond);

static void BM_surrogate_data_small(benchmark::State& state)
{
    byte* data = new byte[state.range(0)];
    set_surrogate_data(data, state.range(0));
    for (auto _ : state) {
        for(size_t i=0; i<ITERATIONS_SMALL; ++i) {
            cesu8::is_valid_cesu8_SSE(data, state.range(0));
        }
    }
    delete [] data;

    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)) * ITERATIONS);
}

BENCHMARK(BM_surrogate_data_small)->RangeMultiplier(2)->Range(SMALL_MIN, SMALL_MAX)->Unit(benchmark::kMicrosecond);

static void BM_surrogate_data(benchmark::State& state)
{
    byte* data = new byte[state.range(0)];
    set_surrogate_data(data, state.range(0));
    for (auto _ : state) {
        for(size_t i=0; i<ITERATIONS; ++i) {
            cesu8::is_valid_cesu8_SSE(data, state.range(0));
        }
    }
    delete [] data;

    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)) * ITERATIONS);
}

BENCHMARK(BM_surrogate_data)->RangeMultiplier(2)->Range(BIG_MIN, BIG_MAX)->Unit(benchmark::kMicrosecond);


static void BM_random_data_small(benchmark::State& state)
{
    byte* data = new byte[state.range(0)];
    set_random_data(data, state.range(0));
    for (auto _ : state) {
        for(size_t i=0; i<ITERATIONS_SMALL; ++i) {
            cesu8::is_valid_cesu8_SSE(data, state.range(0));
        }
    }
    delete [] data;

    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)) * ITERATIONS);
}

BENCHMARK(BM_random_data_small)->RangeMultiplier(2)->Range(SMALL_MIN, SMALL_MAX)->Unit(benchmark::kMicrosecond);

static void BM_random_data(benchmark::State& state)
{
    byte* data = new byte[state.range(0)];
    set_random_data(data, state.range(0));
    for (auto _ : state) {
        for(size_t i=0; i<ITERATIONS; ++i) {
            cesu8::is_valid_cesu8_SSE(data, state.range(0));
        }
    }
    delete [] data;

    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)) * ITERATIONS);
}

BENCHMARK(BM_random_data)->RangeMultiplier(2)->Range(BIG_MIN, BIG_MAX)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
