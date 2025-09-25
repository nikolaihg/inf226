# INF226 Weekly Exercise 1 pwntools

## Connecting to server
```python
from pwn import *

context.log_level = 'debug'

io = remote('inf226.puffling.no', 6001)
print(io.recvline())
```
Output:
```bash
(.venv) nikolai@LAPTOP-6UOFH1KM:~/documents/inf226/weekly-exercise1-pwntools (main)$ python3 hello.py
[+] Opening connection to inf226.puffling.no on port 6001: Done
[DEBUG] Received 0x1d bytes:
    b'Please enter the secret sign\n'
b'Please enter the secret sign\n'
[*] Closed connection to inf226.puffling.no port 6001
```

## Finding secret
Run `extract.py` and test string candidates (`infA`).

## Solve the math tasks
Run `solve.py`

## Finding the secret manually
Look for possible secret strings the output.

### strings
```bash
nikolai@LAPTOP-6UOFH1KM:~/documents/inf226/weekly-exercise1-pwntools (main)$ strings pwnexercise
(...)
Not correct secret sign, please try again, goodbye
Rumors say that a hacker can complete 1024 math problems (addition or multiplication) in 60s.
%d = ?
congrats!You completed the task!
Wrong, try next time
Please enter the secret sign
infA
(...)
``` 

### objdump
```bash
nikolai@LAPTOP-6UOFH1KM:~/documents/inf226/weekly-exercise1-pwntools (main)$ objdump -s -j .rodata pwnexercise
pwnexercise:     file format elf64-x86-64

Contents of section .rodata:
 402000 01000200 00000000 4e6f7420 636f7272  ........Not corr
 402010 65637420 73656372 65742073 69676e2c  ect secret sign,
 402020 20706c65 61736520 74727920 61676169   please try agai
 402030 6e2c2067 6f6f6462 79650000 00000000  n, goodbye......
 402040 52756d6f 72732073 61792074 68617420  Rumors say that
 402050 61206861 636b6572 2063616e 20636f6d  a hacker can com
 402060 706c6574 65203130 3234206d 61746820  plete 1024 math
 402070 70726f62 6c656d73 20286164 64697469  problems (additi
 402080 6f6e206f 72206d75 6c746970 6c696361  on or multiplica
 402090 74696f6e 2920696e 20363073 2e002564  tion) in 60s..%d
 4020a0 20002563 20002564 203d203f 00256400   .%c .%d = ?.%d.
 4020b0 636f6e67 72617473 21596f75 20636f6d  congrats!You com
 4020c0 706c6574 65642074 68652074 61736b21  pleted the task!
 4020d0 0057726f 6e672c20 74727920 6e657874  .Wrong, try next
 4020e0 2074696d 6500506c 65617365 20656e74   time.Please ent
 4020f0 65722074 68652073 65637265 74207369  er the secret si
 402100 676e0069 6e664100                    gn.infA.
```