#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int i, j;
	for (i = 1; i < 3; i++) {
		for (j = 3; j > 1; j--)
			printf("%d X %d = %d\n", i, j, i*j);
	}

	return 0;
}