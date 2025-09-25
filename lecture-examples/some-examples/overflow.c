#include <stdio.h>
#include <stdlib.h>

int f(int a, int i) {
    int x = 679;
    int b = a * 10;
    int y = 344;
    int *c = &x;

    printf("Arguments: a=%d, i=%d Locals: x=%d, b=%d, y=%d, c=%p\n", a, i, x, b, y, c);
    return c[i];
}

int main(int argc, char **argv) {
    int a = atoi(argv[1]);
    int i = atoi(argv[2]);
    int r = f(a,i);
    printf("Hello! The answer is: f(%d,%d)=%d  (0x%x)\n", a, i, r, r);
}
