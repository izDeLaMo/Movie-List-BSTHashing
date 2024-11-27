#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include "NodeTypes.h"
	using namespace std;

struct Queue {
	BTNode * values [1000];
	int rear, front;
	int size;
};

Queue * initQueue (int size);
bool isEmptyQueue (Queue * q);
int sizeQueue (Queue * q);
void enqueue (Queue * q, BTNode * data);
BTNode * dequeue (Queue * q);

#endif
