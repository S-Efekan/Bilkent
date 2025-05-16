#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef struct {
	int QUEUE[SIZE];
	int front;
	int rear;
}queue_t;


void initialize(queue_t*queue)
{
	queue->front = -1;
	queue->rear = -1;
}


int isEmpty(queue_t queue)
{
	if (queue.rear == -1)
		return 1;
	return 0;
}

int isFull(queue_t queue)
{
	if(queue.front )
}


int put(int array[SIZE])
{

}


int get();




int isFull();





int main()
{







	return (0);
}