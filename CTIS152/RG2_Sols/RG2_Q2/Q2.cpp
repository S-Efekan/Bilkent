#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include "stack_struct.h"

stack_t reverseTheStack ( stack_t s1)
{
	stack_t s2;
	initializeS ( &s2 );

	SType temp;

	while (!isEmptyS ( &s1 ))
	{
		temp = pop ( &s1 );
		push ( &s2, temp );
	}
	return s2;
}

void displayStack ( stack_t S )
{
	SType data;


	printf ( "YEAR		COMP			PHONE		URL\n*****************************************************\n" );

	while (!isEmptyS ( &S ))
	{
		data = pop ( &S );
		printf ( "%d		%s				%s			%s\n", data.year, data.company, data.phone, data.webURL );
	}
}

int main ( )
{
	FILE* bp = fopen ( "companies.bin", "rb" );

	if (bp == NULL)
		printf ( "File error occured!" );
	else
	{
		stack_t comp;
		initializeS ( &comp );

		SType item;

		while (!feof ( bp ))
		{
			fread ( &item.year, sizeof ( int ), 1, bp );
			fread ( item.company, 15, 1, bp );
			fread ( item.phone, 15, 1, bp );
			fread ( item.webURL, 50, 1, bp );
			push ( &comp, item );
		}
		displayStack ( comp );

		printf ( "\n\n\n" );

		comp = reverseTheStack (comp);

		displayStack ( comp );

	}
	return 0;
}