/*
 * buttons.h
 *
 *  Created on: Dec 19, 2018
 *      Author: franc
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#define         ButtonUp 	       GPIO_Pin_11
#define         ButtonDown 	       GPIO_Pin_13
#define         ButtonEnter        GPIO_Pin_15

void initButtons(void);
char get_selected_freq(void);

#endif /* BUTTONS_H_ */
