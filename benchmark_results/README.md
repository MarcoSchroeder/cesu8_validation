# How to compare benchmark results
```
python3 compare_csv.py ./company/
```

The argument should be the path to a directory containing 3 files called "scalar.csv", "sse.csv" and "avx.csv"

# How to create CSV output for benchmarks on new machines

1. Navigate to repo root
2. `mkdir benchmark_results/<new>`
3. Run the following benchmarks

`./build/cesu8_benchmark_scalar --benchmark_out=scalar.csv --benchmark_out_format=csv`

`./build/cesu8_benchmark_sse --benchmark_out=sse.csv --benchmark_out_format=csv`

`./build/cesu8_benchmark_avx2 --benchmark_out=avx2.csv --benchmark_out_format=csv`

`./build/cesu8_benchmark_avx512 --benchmark_out=avx512.csv --benchmark_out_format=csv`

4. Move the created CSV files to the new directory `mv *.csv benchmark_results/<new>`

5. `cd benchmark_results`

6. Postprocess the data `python3 process_csv.py <new> -o <new>/processed_data <--skip512>` (Pass --skip512 if no AVX-512 data available!)

7. Run `cat /proc/cpuinfo > proc_cpuinfo.txt` so we know from which CPU the benchmark came :)

8. Commit changes
