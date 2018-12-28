#include <stdio.h>

int main(void) {
	int i = 1;
	int j = 2;
	int k = 0;
	k = i + j;
	printf("%d + %d = %d\n", i, j, k);
	
	k = i - j;
	printf("%d - %d = %d\n", i, j, k);

	k = i | j;
	printf("%d | %d = %d\n", i, j, k);

	k = i * j;
	printf("%d * %d = %d\n", i, j, k);
	
	k = j / i;
	printf("%d / %d = %d\n", j, i, k);

	k = j % i;
	printf("%d %% %d = %d\n", j, i, k);

	k = j & i;
	printf("%d & %d = %d\n", j, i, k);

	k = -(i + j);
	printf("-(%d + %d) = %d\n", i, j, k);

	k = ~(i + j);
	printf("~(%d + %d) = %d\n", i, j, k);

	return 0;
}
