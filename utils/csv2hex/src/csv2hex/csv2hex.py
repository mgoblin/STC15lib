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

def main():
    args = parse_agrs()
    csv_content = read_csv_content(args.i)

    print(csv_content)

    string_io = io.StringIO(csv_content)
    csvreader = csv.reader(string_io)

    parsed_data = []
    for row in csvreader:
        parsed_data.append(row)

    print(sum(parsed_data, []))

if __name__ == "__main__":
    main()
