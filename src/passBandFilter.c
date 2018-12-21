/*
 * passBandFilter.c
 *
 *  Created on: Dec 19, 2018
 *      Author: franc
 */

#include "passBandFilter.h"
#include "math.h"

static double  myFilter[LENGTH_FILTRE];
static float   cutOffFreqs[NUMBER_OF_CUT_OF_FREQS] = {100.0, 200.0};
static uint8_t newFreqsFlag;
static uint8_t computeFilterFlag;


void initFilter(void)
{
	newFreqsFlag = 0;
	computeFilterFlag = 0;
}

void computeFilter()
{
	float WcA = 2.0 * M_PI * cutOffFreqs[FcA] / (float)FS;
	float WcB = 2.0 * M_PI * cutOffFreqs[FcB]  / (float)FS;
	for (int i = 0; i < LENGTH_FILTRE; i++)
	{
		int index = i - ((LENGTH_FILTRE - 1) / 2);
		if (index == 0)
			myFilter[i] = (WcB - WcA)/M_PI;
		else
			myFilter[i] = (sin(index * WcB) - sin(index * WcA)) / (M_PI * index);

		//myFilter[i] = 1.0f / LENGTH_FILTRE;
	}

}

int readBC_Filtre(BufferCirculaire* p_buffer)
{
	float out = 0;
	int index = p_buffer->tail;
	incrementReadingTailBC();
	for (int i = 0; i < LENGTH_FILTRE; i++)
	{
		out += myFilter[i] * p_buffer->data[index];
		index = (p_buffer->bufferSize + p_buffer->tail - i) % p_buffer->bufferSize;
	}
	return out < 4096.0f ? (int)out : 4096;
}


void updateCutOffFreqs(void)
{
	if (cutOffFreqs[FcB] > cutOffFreqs[FcA]) {
		int temp = cutOffFreqs[FcA];
		cutOffFreqs[FcA] = cutOffFreqs[FcB];
		cutOffFreqs[FcB] = temp;
	}
	else if (cutOffFreqs[FcA] == cutOffFreqs[FcB])
		cutOffFreqs[FcA] -= INCREMENTATION_FREQ;
	newFreqsFlag = 0;
}

uint8_t getNewFreqsFlag(void)
{
	return newFreqsFlag;
}

uint8_t getComputeFilterFlag(void)
{
	return computeFilterFlag;
}

void setComputeFilterFlag(uint8_t new_flag_state)
{
	computeFilterFlag = new_flag_state;
}

void incrementCutOffFreq(cut_off_freqs_t cut_off_freq)
{
	cutOffFreqs[cut_off_freq] += INCREMENTATION_FREQ;
}

void decrementCutOffFreq(cut_off_freqs_t cut_off_freq)
{
	cutOffFreqs[cut_off_freq] -= INCREMENTATION_FREQ;
}

int* getCutOffFreqsHandle(void)
{
	return &cutOffFreqs[0];
}

