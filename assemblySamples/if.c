#include <stdio.h>

int main(void) {
	int i = 1;
	int j = 2;
	if(i == j) {
		printf("if");
	} else if(i == 0) {
		printf("else if");
	} else {
		printf("else");
	}
	return 0;
}
