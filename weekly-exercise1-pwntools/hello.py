from pwn import *

context.log_level = 'debug'

io = remote('inf226.puffling.no', 6001)
print(io.recvline())
io.sendline(b'infA') 
print(io.recvline())
io.interactive()
