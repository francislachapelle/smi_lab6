#ifndef LCD_H_
#define LCD_H_

#include "stdint.h"

#define 	CMD_LCD_CLEAR						0x01
#define		CMD_LCD_HOME						0x02
#define 	CMD_LCD_FUNCTION_2_LINES_8_BITS		0x38
#define		CMD_LCD_DISPLAY_ON					0x0E
#define		CMD_LCD_CHANGE_LINE					0xC0
#define 	NUMBER_OF_ROWS						2
#define		NUMBER_OF_COLS						16

void 	initLcd(void);
void 	writeCommand(unsigned short p_command);
void 	writeSymbol(char * p_symbol, int size_of_symbol);
void 	updateLcd(void);
uint8_t getUpdateLcdFlag(void);
void	setUpdateLcdFlag(uint8_t new_state);

#endif /* LCD_H_ */
