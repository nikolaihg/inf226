#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int f(int a, int b) {
    return a + b;
}

char* lookup(int i) {
        char* buffer[5] = { 
        "apple",
        "orange",
        "pear",
        "banana",
        "tangerine"
    };
    return buffer[i];
}

int main (int argc, char** argv) {
    int a = 3, b = 7;
    printf("%d + %d = %d\n", a, b, f(a,b));
    printf("I like %ss\n", lookup(2));
    printf("I like %ss\n", lookup(10));
}