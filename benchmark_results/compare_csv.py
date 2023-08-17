import os
import csv
import argparse
from typing import List

def read_csv_file(abs_dir_path: str, filename: str) -> List[List[str]]:
    abs_filepath = os.path.join(abs_dir_path, filename)
    if not os.path.exists(abs_filepath):
        err = f'Can\'t find file "{filename}" in "{abs_dir_path}"'
        print(err)
        raise Exception(err)

    with open(abs_filepath) as file:
        rows = list(csv.reader(file))
        return rows[1:]

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('dir', help='Relative path to directory containing .csv files')
    args = parser.parse_args()
    rel_path = args.dir
    abs_path = os.path.abspath(rel_path)
    print(f'Relative path to benchmark directory: "{rel_path}"')
    print(f'Absolute path to benchmark directory: "{abs_path}"')

    filenames = ['scalar.csv', 'sse.csv', 'avx2.csv', 'avx512.csv']
    all_csvs = {}
    print(f'Trying to read {filenames} from benchmark directory')
    for filename in filenames:
        csv_file = read_csv_file(abs_path, filename)
        all_csvs[filename] = csv_file
        print(f'Successfully read file "{filename}"')
    print('Successfully read all files from benchmark directory')

    bm_names = [row[0] for row in all_csvs['scalar.csv']]
    scalar_cpu_times = [float(row[3]) for row in all_csvs['scalar.csv']]
    sse_cpu_times = [float(row[3]) for row in all_csvs['sse.csv']]
    avx_cpu_times = [float(row[3]) for row in all_csvs['avx2.csv']]
    avx512_cpu_times = [float(row[3]) for row in all_csvs['avx512.csv']]

    sse_to_scalar = [scalar/sse for scalar, sse in zip(scalar_cpu_times, sse_cpu_times)]
    avx_to_scalar = [scalar/avx for scalar, avx in zip(scalar_cpu_times, avx_cpu_times)]
    avx512_to_scalar = [scalar/avx512 for scalar, avx512 in zip(scalar_cpu_times, avx512_cpu_times)]

    print('\n\nBenchmark Name, Scalar CPU Time, SSE CPU Time, Scalar/SSE , Scalar/AVX, Scalar/AVX512')
    for i, bm_name in enumerate(bm_names):
        print(f'{i} : {bm_name} : {scalar_cpu_times[i]}, {sse_cpu_times[i]}, {avx_cpu_times[i]}, {sse_to_scalar[i]:.2f}, {avx_to_scalar[i]:.2f}, {avx512_to_scalar[i]:.2f}')
