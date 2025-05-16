#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include "queue_int.h"
#include "stack_int.h"




void carWash ( queue_t* Q, stack_t* S, FILE* fp )
{
	int which;
	char what;
	stack_t temp;
	int id;
	initializeS ( &temp );


	while (fscanf ( fp, "%c %d", &what, &which ) != EOF)
	{
	
		switch (what)
		{
		case 'A':
			if (!isFullS ( S ) && !isEmptyQ(Q))
			{
				push ( S, which );
			}
			else if (isFullS ( S ) && !isFullQ ( Q ))
			{
				insert ( Q, which );
			}
			break;
		case 'D':
			id = pop ( S );
			while (!isEmptyS ( S ) && )
			{
				
			}



		}




	}

}


int main ( void )
{
	FILE* fp = fopen ( "carWash.txt", "r" );
	if (fp == NULL)
		printf ( "File error occured!" );
	else
	{
		stack_t S;
		initializeS ( &S );
		queue_t Q;
		initializeQ ( &Q );
		
		push ( &S, 1 );
		push ( &S, 2 );
		push ( &S, 3 );

		carWash ( &Q, &S, fp );







	}


	return 0;
}