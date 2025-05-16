#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
	srand(time(NULL));

	int i; 
	char gen;

	printf("Enter your gender and age: ");
	scanf("%c %d", &gen, &i);

	if (!(gen >= 'A' && gen <= 'z')) {
		int temp;
		temp = i;
		i = gen;
		gen = temp;
	}

	printf("%c   %d", gen, i);

	return 0;
}
