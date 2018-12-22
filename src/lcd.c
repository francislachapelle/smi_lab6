
#include "lcd.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "timer.h"
#include "string.h"
#include "stdio.h"
#include "passBandFilter.h"
#include "buttons.h"
//#include "keypad.h"

/* Private variables */
static int 		number_of_characters_counter;
static char    	first_line[16] = "SMI_NGFL   ";
static char    	unity[4] = "0 Hz";
static int 		size_of_first_line_string;
static uint8_t	update_lcd_flag;

void initLcd(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	//LCD
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = 0x00FF;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	number_of_characters_counter = 0;
	update_lcd_flag = 1;
	size_of_first_line_string = strlen(first_line);
	//clear
	writeCommand(CMD_LCD_CLEAR);

	//function set : 2 lines, 8 bits and 5x8 dots
	writeCommand(CMD_LCD_FUNCTION_2_LINES_8_BITS);

	//Display on
	writeCommand(CMD_LCD_DISPLAY_ON);


	writeSymbol(first_line, size_of_first_line_string);
	writeCommand(CMD_LCD_CHANGE_LINE);

	updateLcd();
}

void writeCommand(unsigned short p_command)
{
	GPIO_SetBits(GPIOE, p_command & 0x00FF);
	p_command = p_command >> 8;
	GPIO_SetBits(GPIOB, p_command & 0x0006);

	int delay = 1000000;
	while(delay--){};

	GPIO_SetBits(GPIOB, 0x0001);

	delay = 1000000;
	while(delay--){};

	GPIO_ResetBits(GPIOB, 0x0001);

	delay = 1000000;
	while(delay--){};

	GPIO_ResetBits(GPIOB, 0x0006);
	GPIO_ResetBits(GPIOE, 0x00FF);
}

void writeSymbol(char * p_symbol, int size_of_symbol)
{
	for (int i = 0; i < size_of_symbol; ++i)
	{
		unsigned short cmd = 0b10000000000 | p_symbol[i];
		writeCommand(cmd);
	}
}

static char   freqVector[5];
void updateLcd(void)
{
	int freq;
	int* cut_off_freqs = getCutOffFreqsHandle();

	if (get_selected_freq() == 'A')
		freq = (int)cut_off_freqs[FcA];
	else
		freq = (int)cut_off_freqs[FcB];

	writeCommand(CMD_LCD_CLEAR);
	writeSymbol(first_line, size_of_first_line_string);

	writeCommand(CMD_LCD_CHANGE_LINE);

	sprintf(freqVector, "%d", freq);
	writeSymbol(freqVector, strlen(freqVector));
	writeSymbol(unity, strlen(unity));

}

uint8_t getUpdateLcdFlag(void)
{
	return update_lcd_flag;
}
void	setUpdateLcdFlag(uint8_t new_state)
{
	update_lcd_flag = new_state;
}
