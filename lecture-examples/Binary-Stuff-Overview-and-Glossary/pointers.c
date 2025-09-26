#include <stdio.h>

void f() {
	char buffer[16]; // space for 16 characters (uninitialized)
	char *p = buffer; // p == buffer

	buffer[0] = 'h'; // set first char to 'h'
	*(p+1) = 'e'; // you can access the buffer through the pointer
	*(buffer+2) = 'l'; // you can use the array as a pointer
	p[3] = 'l'; // you can use the pointer as an array
	p += 4; // pointer arithmetic
	*(p++) = 'o'; // a common pattern for writing strings
	*(p++) = '\0'; // C strings end with a null character
	printf("%s\n", buffer);
}

void h() {
	struct {
		char buffer[16];
		__int32_t check;
	}locals;

    __int32_t *p = (void*)(locals.buffer+16);  // point past the buffer
    *p = 42;   // write to locals.check
}

int main(int argc, char** argv) {	
	void (*fp)() = &f; // function pointer
	int a = 42;
	int *p = &a; // a pointer to the integer a

	(*fp)(); // call whatever fp points to (f)
	(*p)(); // error: called object is not a function or function pointer
	fp = p; // warning; incompatible pointer type

	fp = (void*)p; // C isn't fuzzy if you just cast the pointer
	(*fp)();

	unsigned long x = 0x401176;
	fp = (void*)x;
	(*fp)(); // calls f()

	char *s = "hello"; // a pinter to a character (-> a string in C)
	printf("p=%p, s=%p\n", p, s);
	printf("p=%p, *p=%d, s=%p, *s=%c, s=\"%s\"\n", p, *p, s, *s, s);

	f();
}
