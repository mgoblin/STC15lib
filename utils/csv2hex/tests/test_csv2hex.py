import unittest
from unittest.mock import patch, mock_open
import csv
import io
from intelhex import IntelHex

# Import the module under test
# Note: Ensure this runs from a location where csv2hex is importable,
# or adjust sys.path accordingly.
from csv2hex.csv2hex import (
    parse_csv,
    convert_to_hex_num,
    read_csv_content,
    convert_to_hex_output
)


class TestCSV2Hex(unittest.TestCase):

    def test_parse_csv_simple(self):
        """Test parsing basic CSV content into a flat list."""
        csv_content = "A,B,C\nD,E,F"
        expected = ['A', 'B', 'C', 'D', 'E', 'F']
        result = parse_csv(csv_content)
        self.assertEqual(result, expected)

    def test_parse_csv_single_row(self):
        """Test parsing single-row CSV."""
        csv_content = "10,20,30"
        expected = ['10', '20', '30']
        result = parse_csv(csv_content)
        self.assertEqual(result, expected)

    def test_parse_csv_empty_cell(self):
        """Test handling of empty cells."""
        csv_content = "10,,30"
        expected = ['10', '', '30']
        result = parse_csv(csv_content)
        self.assertEqual(result, expected)

    def test_convert_to_hex_num_valid(self):
        """Test valid hex string conversion."""
        self.assertEqual(convert_to_hex_num("FF"), 255)
        self.assertEqual(convert_to_hex_num("0"), 0)
        self.assertEqual(convert_to_hex_num("a"), 10)
        self.assertEqual(convert_to_hex_num(" 1A "), 26)  # With spaces

    def test_convert_to_hex_num_invalid_raises(self):
        """Test that invalid hex strings raise ValueError."""
        with self.assertRaises(ValueError):
            convert_to_hex_num("XYZ")

    def test_read_csv_content(self):
        """Test reading CSV content from a file-like object."""
        mock_file_content = "A,B\nC,D"
        file_obj = io.StringIO(mock_file_content)
        result = read_csv_content(file_obj)
        self.assertEqual(result, mock_file_content)
        self.assertTrue(file_obj.closed)

    def test_convert_to_hex_output(self):
        """Test writing parsed data to Intel HEX file."""
        parsed_data = [0x10, 0x20, 0x30]
        filename = "output_test.hex"

        with patch("intelhex.IntelHex.tofile") as mock_tofile:
            convert_to_hex_output(parsed_data, filename)

        # Check that tofile was called with correct args
        mock_tofile.assert_called_once_with(filename, format='hex')

        # Also verify internal dict mapping (optional deep check)
        ih = IntelHex()
        ih.fromdict({addr: val for addr, val in enumerate(parsed_data, start=0)})
        written_dict = {k: ih[k] for k in range(len(parsed_data))}
        expected_dict = dict(enumerate(parsed_data))
        self.assertEqual(written_dict, expected_dict)



if __name__ == '__main__':
    unittest.main()