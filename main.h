#ifndef MAIN_H
#define MAIN_H

#include "msp430.h"
#include "font.h"
#include "matrix.h"
#include "buzzer.h"
#include "ADC10.h"
#include "emoticons.h"

#define PERIOD        0x007C    // period of interrupt for buzzing
#define PRESCALER     1         // prescaler of the TimerA
#define TIME          100       // duration of buzzing
#define FREQ          5         // frequency of the buzzing
#define DEGREE        270         // Angle of rotation (possible values 0; 90; 10; 270, otherwise count as 0)
#define ON            1
#define OFF           0

#define BUTTON_INPUT      P1DIR = P1DIR & (~0x08)     // Button set as input    1.3
#define IS_BUTTON_DOWN    (~P1IN & 0x08)              // check if the button is pressed   1.3

extern char Buzzing_On;
extern unsigned long int Timeout;

void Delay (volatile unsigned long int i);

#endif
