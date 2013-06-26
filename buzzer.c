#include "main.h"
#include "buzzer.h"

/*
Name:
  TimerA_Init
Input:
  Counter - Number to be written in TACCRx registers
  prescaler - divider of the input clock
Output:
  nothing
Description:
  Set the mode of the timer and Output mode.
  In TACCRx registers is written the period of the output manipulations (set/reset/toggle etc.)
  Select the clock source and the prescaler (divider).
*/
void TimerA_Init(unsigned int Counter, unsigned int prescaler)
{
  // configure TimerA mode, values, prescaler, interrupt modes
  int divisor;
  switch (prescaler)
  {
    case 1: divisor = 0x0000; break;
    case 2: divisor = 0x0040; break;
    case 4: divisor = 0x0080; break;
    case 8: divisor = 0x00C0; break;
    default: divisor = 0x0000; break;
  }
    
  
  TACTL &= ~ (MC0 | MC1);    // Stop Mode
  TACTL |= TACLR;            // TimerA Clear
  
  TACCTL0 |= OUTMOD2;      // Output Toggle Mode, Capture/Compare
  TACCR0 = Counter;                 // set Capture/Compare register value
  TACCTL1 |= OUTMOD2;      // Output Toggle Mode, Capture/Compare
  TACCR1 = Counter;                 // set Capture/Compare register value  

  TACTL |= 0x0200 | divisor; // Select the Clock and Input Divider and Prescaler
  TACTL |= MC0;              // Mode: Up
  return;
}

/*
Name:
  Buzzer_Init
Input:
  nothing
Output:
  nothing
Description:
  Set initial values, functions, and data direction on the buzzer's pins.
*/
void Buzzer_Init (void)
{
  TACCR0 = 0x20;
  
  // configure Buzzer pins
  P1DIR |= BUZZER_OUT0_PIN | BUZZER_OUT1_PIN;      // Output direction pins
  P1OUT &= (~BUZZER_OUT0_PIN) | BUZZER_OUT1_PIN;   // Initial state of outputs
  P1SEL |= BUZZER_OUT0_PIN | BUZZER_OUT1_PIN;      // Alternate function pins
  
  TACCR0 = PERIOD;
  
  Buzzer (OFF);     // Turn off the buzzer
  
  return;
}

/*
Name:
  Buzzer_Buzz
Input:
  Time - period of buzzing
  Freq - delaying between toggling the outputs
Output:
  nothing
Description:
  Simple toggling the buzzer's outputs with delay between them
*/
void Buzzer_Buzz (unsigned long int Time, unsigned int Freq)
{
  while (Time--)
  {
    P1OUT ^= (BUZZER_OUT0_PIN | BUZZER_OUT1_PIN);
    Delay (Freq);
  }
  return;
}

/*
Name:
  Buzzer
Input:
  State
Output:
  nothing
Description:
  Turn ON/OFF the buzzer by start/stop the timer counter.
*/
void Buzzer (unsigned char State)
{
  if (State == ON)
    TACTL |= MC0;                  // Mode: Up
  else
    TACTL &= ~(MC0 | MC1);        // Stop Mode

  return;
}

/*
#pragma vector = TIMERA0_VECTOR
__interrupt void Buzzing1 (void)
{
  if (Timeout)
  {
    Timeout--;
    if (Buzzing_On && Timeout >= 3000)
      Buzzer (ON);
    if (!Buzzing_On || Timeout < 3000)
      Buzzer (OFF);
  }
  return;
}

#pragma vector = TIMERA1_VECTOR
__interrupt void Buzzing2 (void)
{
  if (Timeout)
  {
    Timeout--;
    if (Buzzing_On && Timeout >= 3000)
      Buzzer (ON);
    if (!Buzzing_On || Timeout < 3000)
      Buzzer (OFF);
  }
  return;
}
*/
