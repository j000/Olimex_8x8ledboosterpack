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

ADC10 ADC;
LEDmatrix Matrix;

// Simple delay loop with volatile variable to avoid optimizations
void Delay(volatile unsigned long int i) {
	while (i--);
	return;
}

#pragma vector=WDT_VECTOR
__interrupt void wdt_interrupt(void) {
	Matrix.Write_Matrix();
}

int main(void) {
	// local variables definitions
	char released = 1;    // flag variable for button's state
	int Result;    //, AVG;      // last and avarage measured values

// ++++++++++++++++++ Initializations ++++++++++++++++++
	WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer

	// do not left undefined
	P2DIR = 0xFF;
	P2OUT = 0x00;


	//LED_Matrix_Init();
	Matrix.Init();
	TimerA_Init(PERIOD, PRESCALER);
	Buzzer_Init();
	BUTTON_INPUT;
	P1REN |= BIT3;

	//ADC10_Init ();
	//AVG = ADC10_Calibrate (16);
	ADC.Init();
	ADC.Calibrate(/*16*/);

	Matrix.Set_Matrix_Rotate(None, DEGREE);

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
				Matrix.Set_Matrix_Rotate(Laugh, DEGREE);
				Timeout = 20000;
			} else if (Result >= Range[1] && Timeout < 15000) {
				if (Buzzing_On)
					Buzzer(ON);
				Matrix.Set_Matrix_Rotate(Happy, DEGREE);
				Timeout = 15000;
			} else if (Result >= Range[0] && Timeout < 10000) {
				if (Buzzing_On)
					Buzzer(ON);
				Matrix.Set_Matrix_Rotate(Smile, DEGREE);
				Timeout = 10000;
			} else if (!Timeout){
				Matrix.Set_Matrix_Rotate(None, DEGREE);
				Timeout = 0;
			}
	//} else {
	if (Timeout)
		Timeout--; // decreasing time remaining of the current picture
	//}
}
}
