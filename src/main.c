/* Includes */
#include <buttons.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "dac.h"
#include "adc.h"
#include "passBandFilter.h"
#include "timer.h"

#include "lcd.h"
#include "buttons.h"
#include "BufferCirculaire.h"
#include "string.h"

int main(void)
{
	uint8_t filter_calculated = 0;

	initLcd();
	initButtons();
	initBC();
	init_adc();
	init_dac();
	initTimerDelay();
	initTimerEchantillonnage();

	//Main Loop
	while (1)
	{
		if (getNewFreqsFlag())
			updateCutOffFreqs();

		/* TEST À ENLEVER */
		if (filter_calculated == 0)
		{
			computeFilter();
			filter_calculated = 1;
		}
		/* FIN TEST À ENLEVER */

	//Ecrit la 2em ligne
		int* cut_off_freqs = getCutOffFreqsHandle();
		if (get_selected_freq() == 'A')
			updateLcd(cut_off_freqs[FcA]);
		else
			updateLcd(cut_off_freqs[FcB]);
		Delay(30);

	}//End main while
}
