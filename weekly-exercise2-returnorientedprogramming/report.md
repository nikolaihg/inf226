# INF226 Weekly Exercise 2 – Stacks, buffers & return-oriented programming

## Stack frames
### a)
---- stack frame of f() ----
int a                    (local variables)
main()'s frame pointer   (old RBP)
address of line 3        (return address/old RIP)
----------------------------
---- stack frame of main() ----
