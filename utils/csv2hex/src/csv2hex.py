import os
from intelhex import IntelHex

def main():
    # ih = IntelHex()
    # ih.fromfile("./utils/csv2hex/test.bin", format="bin")
    # ih.tofile("./utils/csv2hex/test.hex", format="hex")
    current_directory = os.getcwd()
    print("Current directory:", current_directory)    

if __name__ == "__main__":
    main()