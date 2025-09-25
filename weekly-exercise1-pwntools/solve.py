#!/usr/bin/env python3
"""
Usage: python solve.py password
"""
from pwn import *
import sys
import re

HOST = 'inf226.puffling.no'
PATH = 6001

def main():
    password = sys.argv[1] if len(sys.argv) > 1 else input("Password: ")
    io = remote(HOST, PATH)
    
    print(io.recvline().decode())
    io.sendline(password.encode())
    
    while True:
        try:
            question = io.recvuntil(b'?').decode()
            print(f"Question: {question}")
            
            math_match = re.search(r'(\d+)\s*([\+\-\*/])\s*(\d+)', question)
            if math_match:
                num1, op, num2 = math_match.groups()
                result = eval(f"{num1} {op} {num2}") 
                print(f"Math answer: {result}")
                io.sendline(str(result))
            else:
                io.sendline(b'')
                
        except EOFError:
            final = io.recv()
            print(f"Final: {final.decode()}")
            break

if __name__ == "__main__":
    main()