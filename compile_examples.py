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


from SCons.Script import SConscript

Import("env")

print("Building examples")

env.SConscript('examples/SConstruct', exports = 'env')

base_dir = env.subst("$BUILD_DIR") + "/examples"

mem_files_list = find_mem_files(base_dir)
print(f"{mem_files_list}")


print("Build examples finished")

