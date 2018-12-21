/*
 * BufferCirculaire.c
 *
 *  Created on: Dec 19, 2018
 *      Author: franc
 */


#include <BufferCirculaire.h>

static 	BufferCirculaire myBC;


void initBC(void)
{
	myBC.bufferSize = CIRCULAR_BUFFER_SIZE;
	myBC.tail = 0;
	myBC.head = 0;
	myBC.maxHeadIndex = 0;
	for (int i = 0; i < myBC.bufferSize; i++)
		myBC.data[i] = 0;
}

int readBC(void)
{
	int out = myBC.data[myBC.tail];
#if EXTERNAL_TAIL_INCREMENTATION == 0
	incrementReadingTailBC();
#endif
	return out;
}

void writeBC(int p_data)
{
	myBC.data[myBC.head] = p_data;
	myBC.maxHeadIndex = myBC.maxHeadIndex <= myBC.head ? myBC.head
													   : myBC.maxHeadIndex;
	myBC.head++;
	myBC.head %= myBC.bufferSize;
}

void incrementReadingTailBC(void)
{
	myBC.tail++;
	myBC.tail %= myBC.bufferSize;
}

BufferCirculaire*	getBCHandle(void)
{
	return &myBC;
}
