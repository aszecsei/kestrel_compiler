#include <stdio.h>

int mdouble(int input) {
	return 2 * input;
}

int main(void) {
	int i = 1;
	i *= 10;
	i = i - 5;
	int j = mdouble(i);
	printf("i=%d\nj=%d\n", i, j);
	printf("HI THERE\n");
	return 0;
}
