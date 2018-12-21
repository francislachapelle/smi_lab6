/*
 * keypad.c
 *
 *  Created on: Dec 19, 2018
 *      Author: franc
 */

#include <buttons.h>
#include "passBandFilter.h"

char Freq_Select = 'A';

void initButtons()
{

	//GPIO Pins
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = ButtonUp | ButtonDown | ButtonEnter;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN; //GPIO_PuPd_UP
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	// Enable clock for SYSCFG
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	EXTI_InitTypeDef EXTI_InitStruct;
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource11 | EXTI_PinSource13 | EXTI_PinSource15);
	EXTI_InitStruct.EXTI_Line = EXTI_Line11 | EXTI_Line13 | EXTI_Line15;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/* Triggers on rising and falling edge */
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;		//A changer pour seulement 1 des 2!!!!!!!!!!!!!
	EXTI_Init(&EXTI_InitStruct);

	/* Add IRQ vector to NVIC */
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

char get_selected_freq(void)
{
	return Freq_Select;
}


void EXTI15_10_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line11) != RESET) {
		//Button Up
		if (Freq_Select == 'A')
			incrementCutOffFreq(FcA);
		else
			incrementCutOffFreq(FcB);

		EXTI_ClearITPendingBit(EXTI_Line11);
	}
	else if (EXTI_GetITStatus(EXTI_Line13) != RESET) {
		//Button Down
		if (Freq_Select == 'A')
			decrementCutOffFreq(FcA);
		else
			decrementCutOffFreq(FcB);

		EXTI_ClearITPendingBit(EXTI_Line13);
	}
	else if (EXTI_GetITStatus(EXTI_Line15) != RESET) {
		//Button Enter
		if (Freq_Select == 'A')
			Freq_Select = 'B';
		else
			Freq_Select = 'A';
		setComputeFilterFlag(1);

		EXTI_ClearITPendingBit(EXTI_Line15);
	}
}
