import argparse
import csv
import os
from typing import List

def read_csv(filepath: str) -> List[List[str]]:
    with open(filepath) as file:
        rows = list(csv.reader(file))
        return rows[1:]

def extract_cpu_time(data):
    return [row[3] for row in data]

def calc_speedup(baseline: [str], new: [str]) -> [float]:
    baseline_float = [float(x) for x in baseline]
    new_float = [float(x) for x in new]
    speedups = [b/n for b, n in zip(baseline_float, new_float)]
    return speedups

def write_file(path: str, header: [str], data):
    with open(path, 'w') as f:
        csv_writer = csv.writer(f)
        csv_writer.writerow(header)
        csv_writer.writerows(data)
        print(f'Successfully created "{path}"')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('input_dir', help='Directory containing benchmark results as .csv files')
    parser.add_argument('-o', help='Relative path to output directory', required=True)
    args = parser.parse_args()
    input_dir_abs_path = os.path.abspath(args.input_dir)
    output_dir_abs_path = os.path.abspath(args.o)
    print(f'Absolute path to input directory: "{input_dir_abs_path}"')
    print(f'Absolute path to output directory: "{output_dir_abs_path}"')

    # Read original CSV files
    scalar_csv = read_csv(os.path.join(input_dir_abs_path, 'scalar.csv'))
    sse_csv = read_csv(os.path.join(input_dir_abs_path, 'sse.csv'))
    avx2_csv = read_csv(os.path.join(input_dir_abs_path, 'avx2.csv'))
    avx512_csv = read_csv(os.path.join(input_dir_abs_path, 'avx512.csv'))

    # Extract CPU times
    scalar_cpu_time_ascii = extract_cpu_time(scalar_csv[:17])
    print(f'scalar_cpu_time_ascii: {scalar_cpu_time_ascii}')
    scalar_cpu_time_hangul = extract_cpu_time(scalar_csv[17:34])
    scalar_cpu_time_random = extract_cpu_time(scalar_csv[34:51])

    sse_cpu_time_ascii = extract_cpu_time(sse_csv[:17])
    sse_cpu_time_hangul = extract_cpu_time(sse_csv[17:34])
    sse_cpu_time_random = extract_cpu_time(sse_csv[34:51])

    avx2_cpu_time_ascii = extract_cpu_time(avx2_csv[:17])
    avx2_cpu_time_hangul = extract_cpu_time(avx2_csv[17:34])
    avx2_cpu_time_random = extract_cpu_time(avx2_csv[34:51])

    avx512_cpu_time_ascii = extract_cpu_time(avx512_csv[:17])
    avx512_cpu_time_hangul = extract_cpu_time(avx512_csv[17:34])
    avx512_cpu_time_random = extract_cpu_time(avx512_csv[34:51])

    # Calculate cpu time speedup compared to scalar
    sse_speedup_ascii = calc_speedup(scalar_cpu_time_ascii, sse_cpu_time_ascii)
    sse_speedup_hangul = calc_speedup(scalar_cpu_time_hangul, sse_cpu_time_hangul)
    sse_speedup_random = calc_speedup(scalar_cpu_time_random, sse_cpu_time_random)

    avx2_speedup_ascii = calc_speedup(scalar_cpu_time_ascii, avx2_cpu_time_ascii)
    avx2_speedup_hangul = calc_speedup(scalar_cpu_time_hangul, avx2_cpu_time_hangul)
    avx2_speedup_random = calc_speedup(scalar_cpu_time_random, avx2_cpu_time_random)

    avx512_speedup_ascii = calc_speedup(scalar_cpu_time_ascii, avx512_cpu_time_ascii)
    avx512_speedup_hangul = calc_speedup(scalar_cpu_time_hangul, avx512_cpu_time_hangul)
    avx512_speedup_random = calc_speedup(scalar_cpu_time_random, avx512_cpu_time_random)

    # Create dataset files per character type
    lengths = [2**i for i in range(6, 23)]
    header_character_type = ['length', 'scalar', 'sse', 'avx2', 'avx512',
                            'sse_speedup', 'avx2_speedup','avx512_speedup']

    ascii_data = zip(lengths, scalar_cpu_time_ascii, sse_cpu_time_ascii,
                     avx2_cpu_time_ascii, avx512_cpu_time_ascii, sse_speedup_ascii,
                     avx2_speedup_ascii, avx512_speedup_ascii)
    hangul_data = zip(lengths, scalar_cpu_time_hangul, sse_cpu_time_hangul,
                     avx2_cpu_time_hangul, avx512_cpu_time_hangul, sse_speedup_hangul,
                     avx2_speedup_hangul, avx512_speedup_hangul)
    random_data = zip(lengths, scalar_cpu_time_random, sse_cpu_time_random,
                     avx2_cpu_time_random, avx512_cpu_time_random, sse_speedup_random,
                     avx2_speedup_random, avx512_speedup_random)

    # Create dataset files per instruction set
    header_instruction_set = ['length', 'ascii', 'hangul', 'random']

    scalar_data = zip(lengths, scalar_cpu_time_ascii, scalar_cpu_time_hangul,
                      scalar_cpu_time_random)
    sse_data = zip(lengths, sse_cpu_time_ascii, sse_cpu_time_hangul,
                      sse_cpu_time_random)
    avx2_data = zip(lengths, avx2_cpu_time_ascii, avx2_cpu_time_hangul,
                      avx2_cpu_time_random)
    avx512_data = zip(lengths, avx512_cpu_time_ascii, avx512_cpu_time_hangul,
                      avx512_cpu_time_random)

    # Write output
    if not os.path.exists(output_dir_abs_path):
        print(f'Output directory "{output_dir_abs_path}" does not exist')
        os.makedirs(output_dir_abs_path)
        print(f'Successfully created output directory {output_dir_abs_path}')

    # Ascii data
    path_ascii = os.path.join(output_dir_abs_path, 'ascii.csv')
    write_file(path_ascii, header_character_type, ascii_data)

    # Hangul data
    path_hangul = os.path.join(output_dir_abs_path, 'hangul.csv')
    write_file(path_hangul, header_character_type, hangul_data)

    # Random data
    path_random = os.path.join(output_dir_abs_path, 'random.csv')
    write_file(path_random, header_character_type, random_data)

    # Scalar data
    path_scalar = os.path.join(output_dir_abs_path, 'scalar.csv')
    write_file(path_scalar, header_character_type, scalar_data)

    # SSE
    path_sse = os.path.join(output_dir_abs_path, 'sse.csv')
    write_file(path_sse, header_character_type, sse_data)

    # AVX-2
    path_avx2 = os.path.join(output_dir_abs_path, 'avx2.csv')
    write_file(path_avx2, header_character_type, avx2_data)

    # AVX-512
    path_avx512 = os.path.join(output_dir_abs_path, 'avx512.csv')
    write_file(path_avx512, header_character_type, avx512_data)
