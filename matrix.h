#ifndef MATRIX_H
#define MATRIX_H

#define DATA_LATCH_PIN BIT4 // P1.4
#define SPI_CLK_OUT_PIN BIT5 // P1.5
#define SPI_DATA_OUT_PIN BIT6 // P1.6

extern unsigned char Matrix[8];

void TimerA_Init(unsigned int Counter, unsigned int prescaler);

void USI_Init (void);

void LED_Matrix_Init (void);

void Set_Matrix (const unsigned char New[], int Count);

void Set_Matrix_Rotate (const unsigned char New[], int Degree);

__interrupt void Write_Matrix (void);

#endif
