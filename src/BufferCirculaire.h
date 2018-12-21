#ifndef BUFFERCIRCULAIRE_H
#define BUFFERCIRCULAIRE_H

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#define			CIRCULAR_BUFFER_SIZE 			21
#define			EXTERNAL_TAIL_INCREMENTATION    1

//Buffer Circulaire pour la reception des donnees
typedef  struct {
	int data[1024];
	int bufferSize;
	int tail;
	int head;
	int maxHeadIndex;
} BufferCirculaire;

void				initBC(void);
int  				readBC(void);
void 				writeBC(int p_data);
void				incrementReadingTailBC(void);
BufferCirculaire*	getBCHandle(void);


#endif //BUFFERCIRCULAIRE_H
