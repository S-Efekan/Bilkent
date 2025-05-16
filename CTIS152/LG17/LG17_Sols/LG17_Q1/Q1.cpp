#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include "queue_int.h"  //converted to string queue
#define FUELPRICE 22.84
#define DIESELPRICE 21.42

// Diesel price is 21.42 TL per liter.
// Fuel price is 22.84 TL per liter.




void readFromFile(FILE* fp, queue_t* Q) {
	if (fp == NULL)
		printf("File error occured!");
	else {
		int i = Q->front;
		queue_t temp;
		while (fscanf(fp, "%s %c %lf", temp.plate[i], &temp.fuel[i], &temp.liter[i]) != EOF) {

			
			
			

			if (temp.fuel[i] == 'F')
				insert(Q, temp.plate[i], temp.fuel[i], temp.liter[i],temp.liter[i] * FUELPRICE);
			else
				insert(Q, temp.plate[i], temp.fuel[i], temp.liter[i], temp.liter[i] * DIESELPRICE);
			
		}
	}
}

void dailyReport(queue_t* Q) {
	
	printf("Plate		FuelType	Liter	Payment\n*********	********	*****	**********\n");
	double total_l = 0, total_p = 0;

	while (!(isEmptyQ(Q))) {
		int idx = Q->front;
		printf("%-15s	%-15c	%-15.2f	%-15.2f\n", Q->plate[idx], Q->fuel[idx], Q->liter[idx], Q->price[idx]);
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