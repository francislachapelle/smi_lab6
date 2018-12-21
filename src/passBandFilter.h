/*
 * passBandFilter.h
 *
 *  Created on: Dec 19, 2018
 *      Author: franc
 */

#ifndef PASSBANDFILTER_H_
#define PASSBANDFILTER_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "BufferCirculaire.h"
#include "timer.h"

#define		LENGTH_FILTRE			21
#define		INCREMENTATION_FREQ 	10
#define		FS 				    	SAMPLING_FREQUENCY

typedef enum
{
	  FcA = 0
	, FcB = 1
	, NUMBER_OF_CUT_OF_FREQS
} cut_off_freqs_t;

void 	initFilter(void);
int  	readBC_Filtre(BufferCirculaire* p_buffer);
void 	computeFilter(void);
uint8_t	getNewFreqsFlag(void);
uint8_t getComputeFilterFlag(void);
void	setComputeFilterFlag(uint8_t new_flag_state);
void 	incrementCutOffFreq(cut_off_freqs_t cut_off_freq);
void 	decrementCutOffFreq(cut_off_freqs_t cut_off_freq);
void 	updateCutOffFreqs(void);
int*	getCutOffFreqsHandle(void);

#endif /* PASSBANDFILTER_H_ */
