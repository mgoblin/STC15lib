import argparse
import csv
import io
from intelhex import IntelHex

def parse_agrs():
    """
    Parse command-line arguments.

    Returns:
        argparse.Namespace: Parsed arguments with input and output file handlers.
    """

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
    """
    Read content from a given file handle.

    Args:
        f (io.TextIOWrapper): File handle to the CSV file.

    Returns:
        str: Content of the CSV file as a string.
    """

    try:
        csv_content = f.read()
        return(csv_content)
    finally:
        # Ensure the file is closed
        f.close()

def parse_csv(csv_content):
    """
    Parse CSV content into a flat list of strings.

    Args:
        csv_content (str): Raw CSV content as a string.

    Returns:
        list: Flattened list of CSV values (strings).
    """

    string_io = io.StringIO(csv_content)
    csv_reader = csv.reader(string_io)
    parsed_data = []
    for row in csv_reader:
        parsed_data.append(row)
    return sum(parsed_data, [])

def convert_to_hex_num(str_data):
    """
    Convert a hexadecimal string to an integer.

    Args:
        str_data (str): String representing a hexadecimal number.

    Returns:
        int: Integer value of the hexadecimal string.
    """

    return int(str_data.strip(), 16)

def convert_to_hex_output(parsed_data, filename):
    """
    Convert and write to file parsed CSV data into Intel Hex format.

    Args:
        parsed_data (list): List of parsed CSV data.
        filename (str): Output file name.
    """
    ih = IntelHex()
    start_addr = 0
    ih.fromdict({addr: val for addr, val in enumerate(parsed_data, start=start_addr)})
    ih.tofile(filename, format='hex')

        
def main():
    args = parse_agrs()
    csv_content = read_csv_content(args.i)

    parsed_data = [convert_to_hex_num(item) for item in parse_csv(csv_content) if convert_to_hex_num(item)]

    convert_to_hex_output(parsed_data, args.o.name)

if __name__ == "__main__":
    main()
