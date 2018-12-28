#include <stdio.h>

int myfunc(int i) {
	printf("Doubling %d\n", i);
	return i * 20;
}

int main(void) {
	printf("Main function\n");
	int i = 10;
	i = myfunc(i);
	printf("Doubled: %d\n", i);
	return 0;
}
