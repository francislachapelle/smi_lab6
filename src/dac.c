/*
 * dac.c
 *
 *  Created on: Dec 18, 2018
 *      Author: franc
 */

#include <dac.h>

void init_dac(void)
{
	// Enable clock for DAC, and GPIOA
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// Init GPIOA pin 4 (PA4) for DAC output
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	//Init DAC
	DAC_InitTypeDef DAC_InitStruct;

	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_Software;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;

	DAC_Init(DAC_Channel_1, &DAC_InitStruct);
	DAC_Cmd(DAC_Channel_1, ENABLE);
}

void write_dac(uint16_t Data)
{
	// Start ADC conversion
	DAC_SetChannel1Data(DAC_Align_12b_R, Data);

	// Triggers transfer from DAC_DHR12R1 to DAC_DOR
	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
}
