#pragma once
#ifndef SIMD_HGUARDS_HPP
#define SIMD_HGUARDS_HPP

#if defined(__SSE4_2__)
#define CESU8_VALIDATION_SSE_IMPLEMENTATION
#endif

#if defined(__AVX2__)
#define CESU8_VALIDATION_AVX_IMPLEMENTATION
#endif

#if defined(__AVX512F__) && defined(__AVX512BW__)
#define CESU8_VALIDATION_AVX512_IMPLEMENTATION
#endif

#endif // #ifndef SIMD_HGUARDS_HPP