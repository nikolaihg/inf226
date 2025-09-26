// layout.c
#include <stdio.h>
#include <stdlib.h>

char b[4096];
char d[4096] = "data";

int main(int argc, char** argv) {
    int a = 3;
    void *p = malloc(1000); 
    printf("Address of local variable a:                %16p  [stack]\n", &a);
    printf("Address of heap-allocated memory:           %16p  [heap]\n", p);
    printf("Address of uninitialized global variable b: %16p  [bss]\n", &b);
    printf("Address of initialized global variable d:   %16p  [data]\n", &d);
    printf("Address of constant string \"foo\":           %16p  [rodata]\n", &"foo");
    printf("Address of function main:                   %16p  [text]\n", &main);

    return 0;
}
