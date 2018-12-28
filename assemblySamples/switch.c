#include <stdio.h>

int main(void) {
	int i = 2;
	switch(i) {
		case 0:
			printf("case 0");
		case 1:
			printf("case 1");
			break;
		default:
			printf("default");
			break;
	}
	return 0;
}
