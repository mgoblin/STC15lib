# csv2hex utility

## What is it
This converter takes a CSV file and transforms it into an Intel Hex file. Its main purpose is to generate firmware for programming EEPROMs.

## csv2hex usage

```bash
python3 csv2hex.py [-i csv file name] [-o hex file name]
```

When no input file is specified with -i, the converter will automatically look for a file named input.csv. Likewise, if the output file is not defined with -o, the resulting Intel Hex file will be saved as output.hex.

## How to run unit tests from terminal on Linux
Run all commands from csv2hex folder.

1. Acivate virtual env
``` bash
source .venv/bin/activate
```

2. Run unittests
```bash
poetry run python -m unittest discover tests
```

3. Run unit tests with coverate
```bash
poetry run coverage run -m unittest discover tests
```

4. Make HTML test coverage report
```bash
poetry run coverage html
```
Open index.html from htmlcov subfolder.

