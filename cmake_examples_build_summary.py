# Prepare and print the examples build summary
# This is a Python script that runs in CMake STC15Lib build.
# Get one argument from command line 
# which should be mem_list.txt file

from __future__ import print_function
import sys
import re
import os

firmware_mem_files = sys.argv[1]
with open(firmware_mem_files) as fp:
    maps_paths = fp.read()
    for line in maps_paths.split(';'):
        with open(line) as map_file:
            content = map_file.read()
            pattern = r"ROM/EPROM/FLASH\s+[a-fx\d]+\s+[a-fx\d]+\s+(\d+).*"
            matches = re.search(pattern, content, re.MULTILINE)
            hex_name = os.path.basename(map_file.name).split('.')[0] + ".hex"
            if matches:
                print(f"{hex_name:<60}{matches.group(1)} bytes")
            else:
                print(f"{hex_name:<60}No size found")
