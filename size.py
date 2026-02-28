from __future__ import print_function
import sys
import re


firmware_mem = sys.argv[1]
with open(firmware_mem) as fp:
    content = fp.read()
    pattern = r"ROM/EPROM/FLASH\s+[a-fx\d]+\s+[a-fx\d]+\s+(\d+).*"
    matches = re.search(pattern, content, re.MULTILINE)
    print(f"Firmware {sys.argv[2]} size is {matches.group(1)} bytes")
