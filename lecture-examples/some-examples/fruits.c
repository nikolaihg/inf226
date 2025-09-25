#include <stdio.h>
#include <stdlib.h>

int main() {
    char* buffer[5] = { 
        "apple",
        "orange",
        "pear",
        "banana",
        "tangerine"
    };
    char answer[5];
    int choice;

    printf("Please make a choice:\n");

    for(int i = 0 ; i < 5; ++i) {
        printf("%d. %s\n", i+1, buffer[i]);
    }

    fgets(answer, 5, stdin);
    choice = atoi(answer);

    printf("Here you go: One %s for you!\n",buffer[choice-1]);

    return 0;
}
