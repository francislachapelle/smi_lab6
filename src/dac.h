/*
 * dac.h
 *
 *  Created on: Dec 18, 2018
 *      Author: franc
 */

#ifndef DAC_H_
#define DAC_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void init_dac(void);
void write_dac(uint16_t Data);

#endif /* DAC_H_ */
