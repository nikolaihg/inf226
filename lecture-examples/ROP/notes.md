# over.c — essentials

A tiny cheatsheet for building `.o` and inspecting with `objdump`.

## Build object file

```bash
gcc -c -g -O0 -fno-stack-protector -no-pie over.c -o over.o
```

## Link (executable)

```bash
gcc -g -O0 -fno-stack-protector -no-pie over.o -o over
```

## Useful `objdump` commands

* Disassemble with source (Intel syntax):

```bash
objdump -d -S -M intel over.o | less -R
```

* Disassemble linked executable (final addresses):

```bash
objdump -d -S -M intel over | less -R
```

* Show symbols / relocations / sections:

```bash
objdump -t over.o
readelf -r over.o
readelf -S over.o
```

## Quick tips

* Use `-g` and `-O0` while learning to keep code readable and include source lines.
* `.o` is relocatable; the linked executable shows runtime addresses.
* For gadget hunting use the non-PIE executable addresses.
