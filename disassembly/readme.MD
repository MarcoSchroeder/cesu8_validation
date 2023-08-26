 objdump -d -M intel build/CMakeFiles/cesu8_benchmark_scalar.dir/src/cesu8_scalar.cpp.o > scalar.asm

objdump -d -M intel build/CMakeFiles/cesu8_benchmark_sse.dir/src/cesu8_SSE.cpp.o > sse.asm

objdump -d -M intel build/CMakeFiles/cesu8_benchmark_avx2.dir/src/cesu8_AVX2.cpp.o > avx2.asm

objdump -d -M intel build/CMakeFiles/cesu8_benchmark_avx512.dir/src/cesu8_AVX512.cpp.o > avx512.asm