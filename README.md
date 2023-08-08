# cesu8_validation
## Setup 
1. Clone repo
2. Configure cmake project `cmake -S . -B build` (from repo root)
3. Build project `cmake --build build`

## Running tests
The test are located in `./build/`. There is a script in repo root that executes all tests automatically, alternatively the tests can be run individually from the build directory

**Script running all tests**:  `./run_all_tests.sh`

**Individually**:
```
./build/cesu8_validation_test_scalar
./build/cesu8_validation_test_sse
./build/cesu8_validation_test_avx
./build/cesu8_stats_test
```

## Running benchmarks
The benchmarks are located in `./build/` and must be run individually:
```
./build/cesu8_benchmark_scalar
./build/cesu8_benchmark_sse
./build/cesu8_benchmark_avx
```

## Collecting Cesu8 stats
`./build/` contains an executable that collects stats about a Cesu8 encoded file, that is, the number of different codepoints:
`./build/collect_cesu8_stats <filepath>`

**Demo execution**
1. Create a text file containing cesu8: `echo "41CF8FEF8F8FEDA08FEDB08F" | xxd -r -p > output.txt`. The hex literal in "" is the contents of the file. In this case it is a C1-C2-C0-C3-C0-C0-ED-A-C0-ED-B-C0 sequence, i.e., a sequence of 1-byte, 2-byte, 3-byte and surrogate pair code point.
2. Run the executable on the file: ` ./build/collect_cesu8_stats output.txt`. The expected output is:
```
Buffer size:    12
Nr codepoints:  4
Nr 1-byte:      1
Nr 2-byte:      1
Nr 3-byte:      1
Nr surrogate:   1
```

In case the input fail contains invalid cesu8, the output should look like this:
```
terminate called after throwing an instance of 'std::runtime_error'
  what():  invalid cesu8
Aborted
```
