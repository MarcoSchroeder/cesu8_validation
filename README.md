# cesu8_validation
## Setup 
1. Clone repo
2. Configure cmake project `cmake -S . -B build` (from repo root)
3. Build project `cmake --build build`

## Running tests
The tests are located in `./build/` in a single executable.

Run
```
./build/cesu8_validation_test
```

## Running benchmarks
The benchmarks are located in `./build/` and must be run individually:
```
./build/cesu8_benchmark_scalar
./build/cesu8_benchmark_sse
./build/cesu8_benchmark_avx2
./build/cesu8_benchmark_avx512
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
## Converting UTF8 to CESU8
The `./build` directory contains an executable `utf8_to_cesu8` that converts a given utf8 encoded file into a cesu8 encoded file.
Usage: `./build/utf8_to_cesu8 <input_filepath> <output_filepath>` where input_filepath is an existing file containing utf8 and output filepath will be created/overwritten by the program and contain the contents of input filepath converted to cesu8.

**Demo execution**
The directory `./example` contains a UTF-8 encoded file `test.utf8` comprised of the characters: `AéⒺ😀`.
These are a 1-byte, 2-byte, 3-byte, and 4-byte character respectively. In Cesu8-encoding the 4-byte character must be converted to a surrogate pair, the first three characters stay the same.
1. Run ` ./build/utf8_to_cesu8 example/test.utf8 test.cesu8` to convert the utf8 file to cesu8
2. Now collect the cesu8 stats of the newly created file ` ./build/collect_cesu8_stats test.cesu8`

The output should look like this:
```
Buffer size:    12
Nr codepoints:  4
Nr 1-byte:      1
Nr 2-byte:      1
Nr 3-byte:      1
Nr surrogate:   1
```

If there is an error during conversion `utf8_to_cesu8` executable will throw an exception
