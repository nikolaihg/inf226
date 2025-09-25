const char rodata[] = "abcd";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void getFlag(unsigned int mode);
char fox_sound[16] = "pwnpwnpwnpwnpwn";
const char *riddles[] = {
    "rubber duck", "squeak",
    "non-rubber duck", "quack",
    "parrot", "squawk",
    "fox", fox_sound};
void randomize(char *s, unsigned int n);

int main(int argc, char **argv)
{
    setbuf(stdout, NULL); // turn off output buffering
    srand(time(NULL));

    /////////// INTERESTING CODE BELOW //////////////

    unsigned int nRiddles = sizeof(riddles) / sizeof(char *) / 2;
    int start = 0, challenge = 1;
    char animal[16];
    char sound[16];
    char buffer[16];

    printf("Are you ready for a challenge (no/maybe/yes)? ");
    if (!gets(buffer))
        return 1;
    if (tolower(buffer[0]) == 'y')
    {
        randomize(fox_sound, sizeof(fox_sound));
        start = rand() % nRiddles;
        challenge = 2;
    }
    else if (tolower(buffer[0]) == 'n')
    {
        start = 0;
        challenge = 0;
    }
    else
    {
        start = rand() % nRiddles;
        challenge = 1;
    }

    int i;
    for (int k = 0; k < nRiddles; k++)
    {
        i = (start + k) % nRiddles;
        strcpy(animal, riddles[i * 2]);
        strcpy(sound, riddles[i * 2 + 1]);

        printf("What does the %s say? ", animal);

        if (!gets(buffer))
            return 1;

        if (strcmp(buffer, sound) != 0)
        {
            printf("Nope :(\n");
            exit(0);
        }
    }

    printf("You are truly wise in the ways of the %s. Proceed.\n", riddles[i * 2]);

    getFlag(challenge);

    return 0;
}

void getFlag(unsigned int mode)
{
    const char *modes[] = {"easy", "moderate", "hard"};
    if (getenv("TASK_NAME"))
    {
        char cmdline[48];
        snprintf(cmdline, 47, "python ctf.py check %d", mode);
        system(cmdline);
    }
    else
    {
        printf("Success (%s mode)!\n", modes[mode]);
    }
}

void randomize(char *s, unsigned int n)
{
    int i = 0;
    while (i < n - 1)
    {
        s[i++] = rand() % 256;
    }
    s[i] = 0;
}