#include <iostream>
#include "Queue.h"

using namespace std;


Queue * initQueue (int s) {
	Queue * q = new Queue;
	q->front = q->rear = -1;
	q->size = s;
	
	return q;
}


bool isEmptyQueue (Queue * q) {
	if (q->front == -1 && q->rear == -1)
		return true;
	else
		return false;		
}


int sizeQueue (Queue * q) {

	if (isEmptyQueue(q)) {
		return 0;
	}
	
	int sum = 0;
	if (q->front <= q->rear) {
		for (int i=q->front; i<=q->rear; i++)
			sum = sum + 1;
	}
	else {
		int i = q->front;
		while (i < q->size) {
			sum = sum + 1;
			i++;
		} 
		i = 0;
		while (i <= q->rear) {
			sum = sum + 1;
			i++;
		}
	}

	return sum;
}



void enqueue (Queue * q, BTNode * data) {
	if ((q->rear + 1) % q->size == q->front) {
		cout << "Queue is full" << endl;
		return;
	}
	else {
		if (q->front == -1)
			q->front = 0;
			
		q->rear = (q->rear + 1) % q->size;
		q->values[q->rear] = data;
	}
}


BTNode * dequeue (Queue * q) {
	if (isEmptyQueue(q)) {
		cout << "Queue is empty. Dequeue not possible." << endl;
		return NULL; // to indicate error if dequeuing from an empty queue
	}

	BTNode * save = q->values[q->front];
	
	if (q->front == q->rear)
		q->front = q->rear = -1;
	else
		q->front = (q->front + 1) % q->size;
		
	return save;
}

