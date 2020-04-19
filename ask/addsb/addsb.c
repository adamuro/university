#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t addsb (uint64_t num1, uint64_t num2);

void printnum (uint64_t num) {
	for(int i = 0; i < 64; i++) {
		printf("%ld", num & 1);
		num >>= 1;
		if(i % 8 == 7 && i != 0)
			putchar(' ');
	}
	putchar('\n');
}

int main (int argc, char** argv) {
	for(int i = 1; i < argc; i += 2) {
		char* arg = argv[i];
		uint64_t num1 = atoi(arg);
		arg = argv[i + 1];
		uint64_t num2 = atoi(arg);

		printnum(num1);
		printnum(num2);
		printnum(addsb(num1, num2));
		putchar('\n');
	}
}