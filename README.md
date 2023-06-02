# cesu8_simd
Run test:
```
Configure project:
cmake -S . -B build

Build project:
cmake --build build

Run tests:
./build/cesu8_validation_test_scalar
./build/cesu8_validation_test_sse
./build/cesu8_validation_test_avx
```