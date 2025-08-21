#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

void expose_flag() {
    system("cat flag.txt");
}

char* pick_animal() {
    // Array of predetermined strings
    const char *options[] = {
        "Dog",
        "Cat",
        "Giraffe",
        "Sea Horse",
        "Gremlin",
        "Snake",
        "Penguin"
    };

    int num_options = sizeof(options) / sizeof(options[0]);
    srand(time(NULL));
    int random_index = rand() % num_options;

    return options[random_index];
}

int main(int argc, char *argv[]) {
    struct locals {
        char buffer[32];
        char* (*func_pt)();
    } locals;
    locals.func_pt = pick_animal;

    printf("You know what, I'm curious: what is you favourite animal?\n");
    fflush(stdout);

    assert(fgets(locals.buffer, 1024, stdin) != NULL);

    char* animal = locals.func_pt();
    printf("Really? My favourite animal would be a %s\n", animal);

    return 0;
}
