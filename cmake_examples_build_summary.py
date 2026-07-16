# Prepare and print the examples build summary
# This is a Python script that runs in CMake STC15Lib build.
# Get two arguments from command line 
#  - First examples build directory
#  - Second output file name to write the summary

from __future__ import print_function
import sys
import re
import os

def find_mem_files(examples_dir: str) -> list[str]:
    """
    Traverse examples folder and its subfolders to find all files with .mem extension.
    
    Args:
        examples_dir: Path to the examples directory
        
    Returns:
        List of absolute paths to .mem files
    """
    mem_files = []
    
    for root, dirs, files in os.walk(examples_dir):
        for filename in files:
            if filename.endswith('.mem'):
                mem_files.append(os.path.join(root, filename))
    
    return sorted(mem_files)

output_file = sys.argv[2]
maps_paths = find_mem_files(sys.argv[1])

with open(output_file, 'w') as out_fp:
    out_fp.write(f"{len(maps_paths)} .hex files and their sizes:\n")
    for line in maps_paths:
        with open(line.strip()) as mem_file:
            content = mem_file.read()
            pattern = r"ROM/EPROM/FLASH\s+[a-fx\d]+\s+[a-fx\d]+\s+(\d+).*"
            matches = re.search(pattern, content, re.MULTILINE)
            hex_name = os.path.basename(mem_file.name).split('.')[0] + ".hex"
            if matches:
                out_fp.write(f"{hex_name:<60}{matches.group(1)} bytes\n")
            else:
                out_fp.write(f"{hex_name:<60}No size found\n")
