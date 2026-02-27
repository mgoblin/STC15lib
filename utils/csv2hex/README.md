# csv2hex utility

## What is it
This converter takes a CSV file and transforms it into an Intel Hex file. Its main purpose is to generate firmware for programming EEPROMs.

## csv2hex usage

```bash
python3 csv2hex.py [-i csv file name] [-o hex file name]
```

When no input file is specified with -i, the converter will automatically look for a file named input.csv. Likewise, if the output file is not defined with -o, the resulting Intel Hex file will be saved as output.hex.