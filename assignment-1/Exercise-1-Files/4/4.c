#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct wrapper {
    char buffer[16];
    char* identifier;
};

void program(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, char* secret) {
    struct wrapper input_wrapper;
    input_wrapper.identifier = "Guest";

    printf("Weclome, you have access to this program as: %s\n", input_wrapper.identifier);
    printf("What is your favourite number?\n");
    fflush(stdout);

    int offset = 0;
    scanf("%d", &offset);
    getchar();

    printf("My secret message for your number is:\n");
    printf("%lx\n", *(unsigned long*)(input_wrapper.buffer + offset));

    printf("Do you want to know my secret?\n");
    fflush(stdout);

    assert(fgets(input_wrapper.buffer, 1024, stdin) != NULL);

    if (strcmp(input_wrapper.identifier, secret) == 0) {
        printf("My secret is:\n");
        fflush(stdout);
        system("cat flag.txt");
    } else {
        printf("Well, I wont tell my secret to just any guest.\n");
        fflush(stdout);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <secret>\n", argv[0]);
        return EXIT_FAILURE;
    }

    program(1,2,3,4,5,6,argv[1]);
    return 0;
}
