import argparse
import random
import os

random.seed(2103)

def generate_random_ascii_sequence(length: int) -> bytearray:
    return bytearray([random.randint(0, 127) for _ in range(length)])

def generate_random_hangul_code_point() -> bytearray:
    code_point = random.randint(4352, 4607)
    # Hangul characters are encoded as 3-unit ECP
    # 3-unit ECPs carry 16 payload bits
    # 1110|'zzzz 10|yy'yyyy 10|xx'xxxx
    byte1 = 0b1110_0000 | ((code_point >> 12) & 0b1111)
    byte2 = 0b1000_0000 | ((code_point >> 6) & 0b1111_11)
    byte3 = 0b1000_0000 | (code_point & 0b1111_11)
    return bytearray([byte1, byte2, byte3])

def generate_random_hangul_sequence(length: int) -> bytearray:
    ret = bytearray()
    hangul_len, ascii_len = divmod(length, 3)
    for _ in range(hangul_len):
        ret.extend(generate_random_hangul_code_point())
    ascii_ext = generate_random_ascii_sequence(ascii_len)
    ret.extend(ascii_ext)
    return ret

def generate_random_random_sequence(length: int) -> bytearray:
    ret = bytearray()
    bytes_created = 0
    while length-bytes_created >= 6:
        x = random.randint(1, 4)
        if x == 1: # 1-unit code point
            ret.extend([0])
            bytes_created += 1
        elif x == 2: # 2-unit code point
            ret.extend([0b1100_0010, 0b1000_0000])
            bytes_created += 2
        elif x == 3: # 3-unit code point
            ret.extend([0b1110_0000, 0b1010_0000, 0b1000_0000])
            bytes_created += 3
        else: # surrogate pair
            ret.extend([0b1110_1101, 0b1010_0000, 0b1000_0000])
            ret.extend([0b1110_1101, 0b1011_0000, 0b1000_0000])
            bytes_created += 6

    ret.extend([0 for _ in range(length-bytes_created)])
    return ret



if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('chars', choices=['ascii', 'hangul', 'random'], help='Types of code points that should be generated')
    parser.add_argument('-o', help='Relative path to output directory', required=True)
    parser.add_argument('-min', default=6, help='Min power of 2 for length')
    parser.add_argument('-max', default=22, help='Max power of 2 for length')
    args = parser.parse_args()

    print(f'Generating data from characters: "{args.chars}"')
    print(f'Range of generated data length (powers of 2): [{int(args.min)}, {int(args.max)}]')
    abs_path = os.path.abspath(args.o)
    print(f'Absolute path to output directory: "{abs_path}"')

    # Generate data
    generation_fct = None
    if args.chars == 'ascii':
        generation_fct = generate_random_ascii_sequence
    elif args.chars == 'hangul':
        generation_fct = generate_random_hangul_sequence
    elif args.chars == 'random':
        generation_fct = generate_random_random_sequence
    else:
        raise Exception(f'invalid character set: {args.chars}')

    lengths = [2**i for i in range(int(args.min), int(args.max)+1)]
    sequences = []
    print('Generating dataset...')
    for i, l in enumerate(lengths):
        sequences.append(generation_fct(l))
        print(f'Generated {i} of {len(lengths)} strings', end='\r')
    print('Data successfully generated')

    # Write data
    for l, s in zip(lengths, sequences):
        filename = f'random_{args.chars}_length_{l}.cesu8'
        filepath = os.path.join(abs_path, filename)
        with open(filepath, 'wb') as f:
            f.write(s)

    print(f'Successfully wrote {len(lengths)} files to "{abs_path}"')
