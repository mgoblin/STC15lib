from intelhex import IntelHex

def main():
    ih = IntelHex()
    ih[0x0000] = 0x01
    ih[0x0001] = 0x02
    ih[0x0002] = 0x03
    ih.write_hex_file("test.hex")

if __name__ == "__main__":
    main()