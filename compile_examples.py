import os
import re

Import("env")

print("Building examples")

example_build_tasks = env.SConscript('examples/SConstruct', exports = 'env')

Import("env")

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

def flatten(seq):
    for item in seq:
        if isinstance(item, list):
            yield from flatten(item)
        else:
            yield item    

examples_dir = os.path.join(env.subst("$BUILD_DIR"), "examples")

def build_summary_action(source, target, env):
    output_file = target[0].get_abspath()

    # Find all mem files in examples dir. Mem files contains hex size info
    mem_files_list = find_mem_files(examples_dir)
    # Regex pattern to search for hex file size
    pattern = r"ROM/EPROM/FLASH\s+[a-fx\d]+\s+[a-fx\d]+\s+(\d+).*"

    with open(output_file, 'w') as out_fp:
        out_fp.write(f"{len(mem_files_list)} .hex files and their sizes:\n")
        # Iterate through mem files list and print size of each hex file
        for mem_file_name in sorted(mem_files_list):
            with open(mem_file_name.strip()) as mem_file:
                # hex and mem file names are the same
                hex_name = os.path.basename(mem_file_name).split('.')[0] + ".hex"

                mem_file_content = mem_file.read()
                matches = re.search(pattern, mem_file_content, re.MULTILINE)
                if matches:
                    out_fp.write(f"{hex_name:<60}{matches.group(1)} bytes\n")
                else:
                    out_fp.write(f"{hex_name:<60}No size found\n")

    
    with open(output_file, 'r') as out_fp:
        build_summary_content = out_fp.read()
        print(build_summary_content)

post_action = env.Command(
    target = f"{examples_dir}/build_summary.txt",
    source = [],
    action = build_summary_action
)

examples_flatten_list = list(flatten(example_build_tasks))
print(f"Found {len(examples_flatten_list)} example build tasks")
for item in examples_flatten_list:
    print(item[0].name)

env.Depends(post_action, examples_flatten_list)
env.AlwaysBuild(post_action)

env.Default([], post_action)


print(f"Build examples finished")

