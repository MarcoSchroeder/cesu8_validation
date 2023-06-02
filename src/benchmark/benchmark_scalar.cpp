#include <benchmark/benchmark.h>

#include "../cesu8.hpp"
#include "benchmark_common.hpp"



constexpr static size_t iterations_small = 1000;

static void BM_ascii_data(benchmark::State& state)
{
    byte* data = new byte[state.range(0)];
    set_ascii_data(data, state.range(0));
    for (auto _ : state) {
        for(size_t i=0; i<iterations_small; ++i) {
            cesu8::is_valid_cesu8_scalar(data, state.range(0));
        }
    }
    delete [] data;

    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)) * iterations_small);
}

BENCHMARK(BM_ascii_data)->RangeMultiplier(2)->Range(1, 1 << 20)->Unit(benchmark::kMicrosecond);

static void BM_surrogate_data(benchmark::State& state)
{
    byte* data = new byte[state.range(0)];
    set_surrogate_data(data, state.range(0));
    for (auto _ : state) {
        for(size_t i=0; i<iterations_small; ++i) {
            cesu8::is_valid_cesu8_scalar(data, state.range(0));
        }
    }
    delete [] data;

    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)) * iterations_small);
}

BENCHMARK(BM_surrogate_data)->RangeMultiplier(2)->Range(1, 1 << 20)->Unit(benchmark::kMicrosecond);

static void BM_random_data(benchmark::State& state)
{
    byte* data = new byte[state.range(0)];
    set_random_data(data, state.range(0));
    for (auto _ : state) {
        for(size_t i=0; i<iterations_small; ++i) {
            cesu8::is_valid_cesu8_scalar(data, state.range(0));
        }
    }
    delete [] data;

    state.SetItemsProcessed(int64_t(state.iterations()) * int64_t(state.range(0)) * iterations_small);
}

BENCHMARK(BM_random_data)->RangeMultiplier(2)->Range(1, 1 << 20)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
