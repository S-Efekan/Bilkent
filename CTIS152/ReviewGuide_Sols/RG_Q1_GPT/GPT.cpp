#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char name[20];
	int age;
	double gpa;
} stu_t;

void display_record(FILE* file, int record_num) {
	stu_t student;
	fseek(file, record_num * sizeof(stu_t), SEEK_SET);
	if (fread(&student, sizeof(stu_t), 1, file) == 1) {
		printf("%s %d %.2f\n\n", student.name, student.age, student.gpa);
	}
	else {
		printf("Invalid record number!\n\n");
	}
}

int main() {
	FILE* file = fopen("stu.bin", "rb");
	if (file == NULL)
		printf("Error opening file!\n");
	else {
		int choice, x, total_records;

		// Get total records
		fseek(file, 0, SEEK_END);
		total_records = ftell(file) / sizeof(stu_t);

		int current_record = 0;  // Start at the beginning

		do {
			printf("1) Go to record X from top\n");
			printf("2) Move X records ahead\n");
			printf("3) Go X records back from bottom\n");
			printf("4) Exit\n");
			printf("\nEnter your choice: ");
			scanf("%d", &choice);

			if (choice == 1) {
				printf("Enter X: ");
				scanf("%d", &x);
				if (x >= 1 && x <= total_records) {
					current_record = x - 1;
					display_record(file, current_record);
				}
				else {
					printf("Invalid record number!\n\n");
				}
			}
			else if (choice == 2) {
				printf("Enter X: ");
				scanf("%d", &x);
				if (current_record + x < total_records) {
					current_record += x;
					display_record(file, current_record);
				}
				else {
					printf("Out of bounds!\n\n");
				}
			}
			else if (choice == 3) {
				printf("Enter X: ");
				scanf("%d", &x);
				if (total_records - x >= 0) {
					current_record = total_records - x;
					display_record(file, current_record);
				}
				else {
					printf("Out of bounds!\n\n");
				}
			}

		} while (choice != 4);

		fclose(file);
	}
	return 0;
}