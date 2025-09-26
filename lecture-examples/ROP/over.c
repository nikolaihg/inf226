#include <stdio.h>
#include <stdlib.h>

// This is the 'gadget' – the code we want our exploit to run.
// Usually, we might want to do something a bit more interesting
// than saying hello and launching an OpenGL demo – perhaps
// start a (remotely accessible) shell (/bin/sh), or download
// some code and run it, or some else/worse.
// In this case we're *really* lucky (the code does
// exactly what we want) – realistically, we might
// have to find more gadgets and overflow the buffer
// with a whole chain of return addresses (hence
// the name "return-oriented programming")
int launch_shell() {
    printf("U got me!\n");
    system("echo hello");
    system("glxgears");
}

// for debugging – try calling dump_mem(&argv) to see what the stack looks like
// it'll print 8 bytes (one 64-bit pointer) per line
// e.g., input "1234\n" and you'll see 0x…0a34333231… somewhere in the stack dump
void dump_mem(void *mem) {
    void **ptr = (void**)mem;

    for(int i = 0; i < 10; i++) {
        printf("%04lx: 0x%016lx\n", i*sizeof(*ptr), *ptr);
        ptr++;
    }
}

int main(int argc, char** argv) {
    int a = 3;
    char buffer[8];

    printf("Fill the buffer: ");
    fflush(stdout);
    
    fgets(buffer, 256 , stdin);
    // uncomment to see what the stack looks like after overflow
    dump_mem(&argv);
    
    printf("You entered: %s \n", buffer);
    printf("and a = %i \n", a);

    return 0;
}
