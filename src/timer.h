/*
 * timer.h
 *
 *  Created on: Dec 19, 2018
 *      Author: franc
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#define			SAMPLING_FREQUENCY								    80000
#define			SAMPLING_TIME_PRESCALER					     		(84000000 / SAMPLING_FREQUENCY)

void initTimerDelay();
void initTimerEchantillonnage();
void Delay(int p_countdown);

#endif /* TIMER_H_ */
