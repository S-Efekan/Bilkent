#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include "queue_struct.h"  //converted to string queue
#define FUELPRICE 22.84
#define DIESELPRICE 21.42

// Diesel price is 21.42 TL per liter.
// Fuel price is 22.84 TL per liter.




void readFromFile(FILE* fp, queue_t* Q) 
{
	if (fp == NULL)
		printf("File error occured!");
	else {
		cust_t temp;
		while (fscanf(fp, "%s %c %lf", temp.plate, &temp.fuel, &temp.liter) != EOF) 
		{
			if (temp.fuel == 'F')
				temp.payment = temp.liter* FUELPRICE;
			else
				temp.payment = temp.liter* DIESELPRICE;

			insert(Q, temp);

		}
	}
}

void dailyReport(queue_t* Q) {

	printf("Plate		FuelType	Liter	Payment\n*********	********	*****	**********\n");
	double total_l = 0, total_p = 0;

	while (!(isEmptyQ(Q))) {
		int idx = Q->front;
		printf("%-15s	%-15c	%-15.2f	%-15.2f\n", temp.plate, temp.fuel, temp.liter);
		total_l += Q->liter[idx];
		total_p += Q->price[idx];

		remove(Q);
	}

	printf("Total liter sold : %.2f\n", total_l);
	printf("Total payment recieved : %.2f\n", total_p);

}

int main() {
	FILE* fp = fopen("customers.txt", "r");
	queue_t Q;

	initializeQ(&Q);
	readFromFile(fp, &Q);
	dailyReport(&Q);




	return (0);
}