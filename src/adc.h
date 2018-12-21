/*
 * adc.h
 *
 *  Created on: Dec 18, 2018
 *      Author: franc
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "assert.h"

void 	 init_adc(void);
uint16_t read_adc(void);
uint8_t  get_adc_data_ready_flag(void);
void 	 set_adc_data_ready_flag(uint8_t new_flag_state);


#endif /* ADC_H_ */
