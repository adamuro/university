#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t bitrev (uint64_t num);

void printnum (int64_t num) {
	for(int i = 0; i < 64; i++) {
		printf("%ld", num & 1);
		num >>= 1;
		if(i == 31)
			putchar(' ');
	}
	putchar('\n');
}

int main (int argc, char** argv) {
	for(int i = 1; i < argc; i++) {
		char* arg = argv[i];
		int64_t num = atoi(arg);

		printnum(num);
		printnum(bitrev(num));
		putchar('\n');
	}
	return 0;
}