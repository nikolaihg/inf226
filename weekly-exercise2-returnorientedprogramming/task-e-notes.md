## -s 
```
(.venv) nikolai@LAPTOP-6UOFH1KM:~/documents/inf226/weekly-exercise2-returnorientedprogramming (main)$ python stackdump.py
[+] Opening connection to inf226.puffling.no on port 6102: Done
[DEBUG] Sent 0x2 bytes:
    b'-s'
[+] Receiving all data: Done (174B)
[DEBUG] Received 0xae bytes:
    b'0000000000401495\n'
    b'00007ffd5d84fde8\n'
    b'0000000100000000\n'
    b'000000000000732d\n'
    b'f8452961d1228b00\n'
    b'0000000000000001\n'
    b'00007f8557b1b24a\n'
    b'0000000000000000\n'
    b'0000000000401409\n'
    b'0000000100000000\n'
    b'lol\n'
[*] Closed connection to inf226.puffling.no port 6102
0000000000401495
00007ffd5d84fde8
0000000100000000
000000000000732d
f8452961d1228b00
0000000000000001
00007f8557b1b24a
0000000000000000
0000000000401409
0000000100000000
lol
```

## -v
```
(.venv) nikolai@LAPTOP-6UOFH1KM:~/documents/inf226/weekly-exercise2-returnorientedprogramming (main)$ python stackdump.py
[+] Opening connection to inf226.puffling.no on port 6102: Done
[DEBUG] Sent 0x2 bytes:
    b'-v'
[+] Receiving all data: Done (604B)
[DEBUG] Received 0x25c bytes:
    b'----\n'
    b' -40: 0x000000000040150e    0e  15   @  00  00  00  00  00\n'
    b' -32: 0x00007ffe7b5a68b8    b8   h   Z   {  fe  7f  00  00\n'
    b' -24: 0x0000000100000000    00  00  00  00  01  00  00  00\n'
    b' -16: 0x000000000000762d     -   v  00  00  00  00  00  00\n'
    b'  -8: 0xb0ca2f0b6ccc7600    00   v  cc   l  0b   /  ca  b0\n'
    b'----\n'
    b'   0: 0x0000000000000001    01  00  00  00  00  00  00  00\n'
    b'   8: 0x00007f389f6ff24a     J  f2   o  9f   8  7f  00  00\n'
    b'  16: 0x0000000000000000    00  00  00  00  00  00  00  00\n'
    b'  24: 0x0000000000401409    09  14   @  00  00  00  00  00\n'
    b'  32: 0x0000000100000000    00  00  00  00  01  00  00  00\n'
    b'lol\n'
[*] Closed connection to inf226.puffling.no port 6102
----
 -40: 0x000000000040150e    0e  15   @  00  00  00  00  00
 -32: 0x00007ffe7b5a68b8    b8   h   Z   {  fe  7f  00  00
 -24: 0x0000000100000000    00  00  00  00  01  00  00  00
 -16: 0x000000000000762d     -   v  00  00  00  00  00  00
  -8: 0xb0ca2f0b6ccc7600    00   v  cc   l  0b   /  ca  b0
----
   0: 0x0000000000000001    01  00  00  00  00  00  00  00
   8: 0x00007f389f6ff24a     J  f2   o  9f   8  7f  00  00
  16: 0x0000000000000000    00  00  00  00  00  00  00  00
  24: 0x0000000000401409    09  14   @  00  00  00  00  00
  32: 0x0000000100000000    00  00  00  00  01  00  00  00
lol
```

## objdump -d hackme_medium: hackme 
```
0000000000401236 <hackme>:
  401236:       f3 0f 1e fa             endbr64
  40123a:       55                      push   %rbp
  40123b:       48 89 e5                mov    %rsp,%rbp
  40123e:       bf 04 20 40 00          mov    $0x402004,%edi
  401243:       e8 88 fe ff ff          call   4010d0 <puts@plt>
  401248:       bf 01 00 00 00          mov    $0x1,%edi
  40124d:       e8 de fe ff ff          call   401130 <exit@plt>
```
