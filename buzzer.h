#ifndef BUZZER_H
#define BUZZER_H

#define BUZZER_OUT0_PIN BIT1 // P1.1
#define BUZZER_OUT1_PIN BIT2 // P1.2

void Delay (volatile unsigned long int i);

void Buzzer_Init (void);

void Buzzer_Buzz (unsigned long int Time, unsigned int Freq);

void Buzzer (unsigned char State);

/*
__interrupt void Buzzing1 (void);

__interrupt void Buzzing2 (void);
*/

#endif
