# How to compare benchmark results
```
python3 compare_csv.py ./company/
```

The argument should be the path to a directory containing 3 files called "scalar.csv", "sse.csv" and "avx.csv"

# How to create CSV output for benchmarks on new machines

1. Navigate to repo root
2. `mkdir benchmark_results/<new>`
3. `cd benchmark_results/<new>`
4. Run the following benchmarks

`../../build/cesu8_benchmark_scalar --benchmark_out=scalar.csv --benchmark_out_format=csv`

`../../build/cesu8_benchmark_sse --benchmark_out=sse.csv --benchmark_out_format=csv`

`../../build/cesu8_benchmark_avx --benchmark_out=avx.csv --benchmark_out_format=csv`

5. Delete the first 9 lines from the newly created CSV files. They contain CPU info. The first line in the CSV files should be the header row that looks like this:

"name,iterations,real_time,cpu_time,time_unit,bytes_per_second,items_per_second,label,error_occurred,error_message"
