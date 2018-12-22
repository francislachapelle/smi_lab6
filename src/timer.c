/*
 * timer.c
 *
 *  Created on: Dec 19, 2018
 *      Author: franc
 */

#include "timer.h"
#include "adc.h"
#include "dac.h"
#include "passBandFilter.h"

static volatile int DelayCount;

void initTimerDelay()
{
	DelayCount = 0;
	TIM_TimeBaseInitTypeDef TIM_BaseStruct;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable clock for TIM2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_BaseStruct.TIM_Prescaler = 8399;
	TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_BaseStruct.TIM_Period = 9; // 1000Hz PWM
	TIM_BaseStruct.TIM_ClockDivision = 0;
	TIM_BaseStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &TIM_BaseStruct);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	/* Enable the TIM2 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void initTimerEchantillonnage()
{
	TIM_TimeBaseInitTypeDef TIM_BaseStruct;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable clock for TIM4 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	//TIM_BaseStruct.TIM_Prescaler = 8399;
	TIM_BaseStruct.TIM_Prescaler = SAMPLING_TIME_PRESCALER;
	TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_BaseStruct.TIM_Period = 1; // Fs = 10kHz
	TIM_BaseStruct.TIM_ClockDivision = 0;
	TIM_BaseStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4, &TIM_BaseStruct);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM4, ENABLE);

	/* Enable the TIM4 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Delay(int p_countdown)
{
	DelayCount = p_countdown;
	while (DelayCount) {};
}

void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		DelayCount--; //Interrupt tous les 1ms
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void TIM4_IRQHandler()
{
	BufferCirculaire* myBC = getBCHandle();
	if (TIM_GetITStatus(TIM4, TIM_IT_Update))
	{
		writeBC(read_adc());	//Echantillonne a 10kHz avec Tim4 et met data dans le BufferCirculaire
		int valueToPutInDAC = readBC_Filtre(myBC);
		write_dac(valueToPutInDAC);
		//write_dac(read_adc());
		set_adc_data_ready_flag(0);
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}
