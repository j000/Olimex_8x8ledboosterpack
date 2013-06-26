/******************************************************************************
 * File: main.c
 *
 * Created by Aleksandar Mitev (shondll_yahoo.com)
 *
 * Description: Simple file to get started with MSP430-LED-BOOSTERPACK
 ******************************************************************************/

#include "main.h"

char Buzzing_On = 0;            // flag variable for buzzing
unsigned long int Timeout = 0; // remaining time of the state of the display (emoticon)
const unsigned char Range[3] = { 20, 40, 90 };   // noise levels thresholds

// Simple delay loop with volatile variable to avoid optimizations
void Delay(volatile unsigned long int i) {
	while (i--)
		;
	return;
}

int main(void) {
	// local variables definitions
	char released = 1;    // flag variable for button's state
	int Result;    //, AVG;      // last and avarage measured values
	ADC10 ADC;

// ++++++++++++++++++ Initializations ++++++++++++++++++
	WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer
	LED_Matrix_Init();
	TimerA_Init(PERIOD, PRESCALER);
	Buzzer_Init();
	BUTTON_INPUT;
	P1REN |= BIT3;

	//ADC10_Init ();
	//AVG = ADC10_Calibrate (16);
	ADC.Init();
	ADC.Calibrate(16);

	Set_Matrix_Rotate(None, DEGREE);

	__enable_interrupt();         // General Interrupt Enable
// ------------------ Initializations ------------------

	while (1) {
		if (IS_BUTTON_DOWN && released) {
			// Turn ON/OFF the buzzer
			Buzzing_On = !Buzzing_On;
			if (Buzzing_On)
				Buzzer(ON);
			else
				Buzzer(OFF);
			// Mark button as pressed
			released = 0;
		} else if (!IS_BUTTON_DOWN)
			released = 1;   // Mark button as released

		// Leaving some time buzzing gap to avoid feedback sound
		if (Timeout < 4000)
			Buzzer(OFF);

		//if (!Timeout) {
			//Result = ADC10_GetResult (AVG);   // take converted result
			Result = ADC.GetResult();

			// comparing the result with the ranges
			// and set the respective timeout, emoticon and buzzer effect
			if (Result >= Range[2] && Timeout < 20000) {
				if (Buzzing_On)
					Buzzer(ON);
				Set_Matrix_Rotate(Laugh, DEGREE);
				Timeout = 20000;
			} else if (Result >= Range[1] && Timeout < 15000) {
				if (Buzzing_On)
					Buzzer(ON);
				Set_Matrix_Rotate(Happy, DEGREE);
				Timeout = 15000;
			} else if (Result >= Range[0] && Timeout < 10000) {
				if (Buzzing_On)
					Buzzer(ON);
				Set_Matrix_Rotate(Smile, DEGREE);
				Timeout = 10000;
			} else if (!Timeout){
				Set_Matrix_Rotate(None, DEGREE);
				Timeout = 0;
			}
	//} else {
	if (Timeout)
		Timeout--; // decreasing time remaining of the current picture
	//}
}
}
