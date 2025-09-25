#!/usr/bin/env python3
from pwn import *

def main():
    e = ELF('./pwnexercise')
    
    rodata = e.section('.rodata')
    strings = []
    current = b''
    
    for byte in rodata:
        if 32 <= byte <= 126:  # printable ASCII
            current += bytes([byte])
        else:
            if len(current) > 3:
                strings.append(current.decode('ascii'))
            current = b''
    
    print("Strings found in .rodata:")
    for s in strings:
        print(f"  '{s}'")

if __name__ == "__main__":
    main()