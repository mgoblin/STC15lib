import argparse
import csv
import io
from intelhex import IntelHex

def parse_agrs():
    parser = argparse.ArgumentParser(description='Convert csv to hex file')

    parser.add_argument(
        '-i', 
        type=argparse.FileType('r'), 
        help='input csv file',
        default='input.csv'
    )
    parser.add_argument(
        '-o', 
        type=argparse.FileType('w'), 
        help='output hex file',
        default='output.hex'
    )

    args = parser.parse_args()
    return args

def read_csv_content(f):
    try:
        csv_content = f.read()
        return(csv_content)
    finally:
        # Ensure the file is closed
        f.close()

def parse_csv(csv_content):
    string_io = io.StringIO(csv_content)
    csv_reader = csv.reader(string_io)
    parsed_data = []
    for row in csv_reader:
        parsed_data.append(row)
    return sum(parsed_data, [])

def convert_to_hex_num(str_data):
    return int(str_data.strip(), 16)

def main():
    args = parse_agrs()
    csv_content = read_csv_content(args.i)

    parsed_data = [convert_to_hex_num(item) for item in parse_csv(csv_content) if convert_to_hex_num(item)]

    ih = IntelHex()
    start_addr = 0
    ih.fromdict({addr: val for addr, val in enumerate(parsed_data, start=start_addr)})
    ih.tofile(args.o, format='hex')

if __name__ == "__main__":
    main()
