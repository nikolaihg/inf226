#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    struct locals {
        char buffer[16];
        int32_t secret;
    } locals;
    locals.secret = 0x4841434b;

    printf("A new challenger approaches!\n");
    fflush(stdout);
    assert(fgets(locals.buffer, 1024, stdin) != NULL);

    if (locals.secret == 0xc0ffee) {
        printf("You found the flag!\n");
        fflush(stdout);
        system("cat flag.txt");
    } else {
        printf("No flag here\n");
        fflush(stdout);
    }

    return 0;
}
