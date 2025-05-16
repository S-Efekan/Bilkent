#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int choice, age, yes;
	double total, price;
	char yn;

	printf("\nMOVIE TICKET BOOKING\n");
	printf("--------------------\n");
	printf("1. Regular Ticket\n");
	printf("2. VIP Ticket\n");
	printf("3. Child Ticket \n");
	printf("4. EXIT\n");

	printf("Enter your choice: ");
	scanf("%d", &choice);

	total = 0;
	yes = 0;
	while (!(choice == 1 || choice == 2 || choice == 3 || choice == 4))
	{
		printf("Invalid choice! Please enter a valid option (1-4): ");
		scanf("%d", &choice);
	}
	while (choice != 4)
	{
		switch (choice)
		{
		case 1: price = 450;

			printf("Regular Ticket\n");
			printf("Is the booking done before the deadline? (y/n): ");
			scanf(" %c", &yn);
			switch (yn)
			{
			case 'y':
			case 'Y': price = price - 15.0 / 100 * price;
				printf("Booking successful! Payment: %.2f TL\n", price);
				yes += 1;
				break;
			case 'n':
			case 'N':
				printf("Booking successful! Payment: %.2f TL\n", price);
				break;
			}
			total += price;
			break;
		case 2: price = 900;
			printf("VIP Ticket\n");
			printf("Is the booking done before the deadline? (y/n): ");
			scanf(" %c", &yn);
			switch (yn)
			{
			case 'y':
			case 'Y': price = price - 15.0 / 100 * price;
				printf("Booking successful! Payment: %.2f TL\n", price);
				yes += 1;
				break;
			case 'n':
			case 'N':
				printf("Booking successful! Payment: %.2f TL\n", price);
				break;
			}
			total += price;
			break;

		case 3: price = 150;
			printf("CHILD Ticket \n");
			printf("Enter age:");
			scanf("%d", &age);

			while (!(age <= 12 && age > 0))
			{
				printf("Child Ticket is only valid for ages 6-12.");
				printf("Booking unsuccessful! ");
			}

			if (age < 6)
			{
				price = 0;
				printf("Free Ticket for children aged 0-5 :)\n");
				printf("Booking successful! Payment: 0.00 TL\n");
			}
			else
			{
				printf("Is the booking done before the deadline? (y/n): ");
				scanf(" %c", &yn);

				switch (yn)
				{
				case 'y':
				case 'Y': price = price - 15.0 / 100 * price;
					printf("Booking successful! Payment: %.2f TL\n", price);
					yes += 1;
					break;
				case 'n':
				case 'N':
					printf("Booking successful! Payment: %.2f TL\n", price);
					break;
				}
				total += price;
				break;

			}
		}
		printf("\nMOVIE TICKET BOOKING\n");
		printf("--------------------\n");
		printf("1. Regular Ticket\n");
		printf("2. VIP Ticket\n");
		printf("3. Child Ticket \n");
		printf("4. EXIT\n");

		printf("Enter your choice: ");
		scanf("%d", &choice);
	}

	printf("Total booking amount : %.2f TL\n", total);
	printf("No of tickets sold with an early payment discount: %d\n ", yes);

	return 0;
}
