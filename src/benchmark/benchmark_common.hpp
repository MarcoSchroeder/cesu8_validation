#pragma once
#ifndef BENCHMARK_COMMON_HPP
#define BENCHMARK_COMMON_HPP

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

constexpr size_t ITERATIONS = 5000;

std::vector<std::string> const ASCII_FILEPATHS = {
    "benchmark_data/ascii/random_ascii_length_64.cesu8",
    "benchmark_data/ascii/random_ascii_length_128.cesu8",
    "benchmark_data/ascii/random_ascii_length_256.cesu8",
    "benchmark_data/ascii/random_ascii_length_512.cesu8",
    "benchmark_data/ascii/random_ascii_length_1024.cesu8",
    "benchmark_data/ascii/random_ascii_length_2048.cesu8",
    "benchmark_data/ascii/random_ascii_length_4096.cesu8",
    "benchmark_data/ascii/random_ascii_length_8192.cesu8",
    "benchmark_data/ascii/random_ascii_length_16384.cesu8",
    "benchmark_data/ascii/random_ascii_length_32768.cesu8",
    "benchmark_data/ascii/random_ascii_length_65536.cesu8",
    "benchmark_data/ascii/random_ascii_length_131072.cesu8",
    "benchmark_data/ascii/random_ascii_length_262144.cesu8",
    "benchmark_data/ascii/random_ascii_length_524288.cesu8",
    "benchmark_data/ascii/random_ascii_length_1048576.cesu8",
    "benchmark_data/ascii/random_ascii_length_2097152.cesu8",
    "benchmark_data/ascii/random_ascii_length_4194304.cesu8"};

std::vector<std::string> const HANGUL_FILEPATHS = {
    "benchmark_data/hangul/random_hangul_length_64.cesu8",
    "benchmark_data/hangul/random_hangul_length_128.cesu8",
    "benchmark_data/hangul/random_hangul_length_256.cesu8",
    "benchmark_data/hangul/random_hangul_length_512.cesu8",
    "benchmark_data/hangul/random_hangul_length_1024.cesu8",
    "benchmark_data/hangul/random_hangul_length_2048.cesu8",
    "benchmark_data/hangul/random_hangul_length_4096.cesu8",
    "benchmark_data/hangul/random_hangul_length_8192.cesu8",
    "benchmark_data/hangul/random_hangul_length_16384.cesu8",
    "benchmark_data/hangul/random_hangul_length_32768.cesu8",
    "benchmark_data/hangul/random_hangul_length_65536.cesu8",
    "benchmark_data/hangul/random_hangul_length_131072.cesu8",
    "benchmark_data/hangul/random_hangul_length_262144.cesu8",
    "benchmark_data/hangul/random_hangul_length_524288.cesu8",
    "benchmark_data/hangul/random_hangul_length_1048576.cesu8",
    "benchmark_data/hangul/random_hangul_length_2097152.cesu8",
    "benchmark_data/hangul/random_hangul_length_4194304.cesu8"};

std::vector<std::string> const RANDOM_FILEPATHS = {
    "benchmark_data/random/random_random_length_64.cesu8",
    "benchmark_data/random/random_random_length_128.cesu8",
    "benchmark_data/random/random_random_length_256.cesu8",
    "benchmark_data/random/random_random_length_512.cesu8",
    "benchmark_data/random/random_random_length_1024.cesu8",
    "benchmark_data/random/random_random_length_2048.cesu8",
    "benchmark_data/random/random_random_length_4096.cesu8",
    "benchmark_data/random/random_random_length_8192.cesu8",
    "benchmark_data/random/random_random_length_16384.cesu8",
    "benchmark_data/random/random_random_length_32768.cesu8",
    "benchmark_data/random/random_random_length_65536.cesu8",
    "benchmark_data/random/random_random_length_131072.cesu8",
    "benchmark_data/random/random_random_length_262144.cesu8",
    "benchmark_data/random/random_random_length_524288.cesu8",
    "benchmark_data/random/random_random_length_1048576.cesu8",
    "benchmark_data/random/random_random_length_2097152.cesu8",
    "benchmark_data/random/random_random_length_4194304.cesu8"};

using byte = unsigned char;

#endif // #ifndef BENCHMARK_COMMON_HPP
