# Prepare and print the examples build summary
# This is a Python script that runs in CMake STC15Lib build.
# Get two arguments from command line 
#  - First mem_list.txt file
#  - Second output file name to write the summary

from __future__ import print_function
import sys
import re
import os

firmware_mem_file = sys.argv[1]
output_file = sys.argv[2]

with open(firmware_mem_file, 'r') as fp, open(output_file, 'w') as out_fp:
    maps_paths = fp.read()
    out_fp.write("Example .hex files and their sizes:\n")
    for line in maps_paths.split(';'):
        with open(line.strip()) as map_file:
            content = map_file.read()
            pattern = r"ROM/EPROM/FLASH\s+[a-fx\d]+\s+[a-fx\d]+\s+(\d+).*"
            matches = re.search(pattern, content, re.MULTILINE)
            hex_name = os.path.basename(map_file.name).split('.')[0] + ".hex"
            if matches:
                out_fp.write(f"{hex_name:<60}{matches.group(1)} bytes\n")
            else:
                out_fp.write(f"{hex_name:<60}No size found\n")
