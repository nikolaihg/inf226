#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void expose_flag() {
    system("cat flag.txt");
}

int main(int argc, char *argv[]) {
    char buffer[16];

    printf("Welcome explorer, to this wonderous world.\n");
    fflush(stdout);

    int exploration_offset;

    scanf("%d", &exploration_offset);
    getchar();

    printf("You expolore and find:\n");
    printf("%\lx\n", *(unsigned long*)(buffer + exploration_offset));

    printf("Now, try to find the flag!\n");
    fflush(stdout);

    assert(fgets(buffer, 1024, stdin) != NULL);

    return 0;
}
