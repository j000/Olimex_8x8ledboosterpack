#include "main.h"
#include "matrix.h"

// Global variable Matrix - the actual container of data which will be displayed on the LED matrix
unsigned char Matrix[8];

/*
 Name:
 USI_Init
 Input:
 nothing
 Output:
 nothing
 Description:
 Configures the serial interface with the proper settings.
 */
void USI_Init(void) {
	// configure SPI
	USICTL0 |= USISWRST;                      // USI in reset
	USICTL0 = USICTL0 | USILSB;               // Least Significant Bit first
	USICTL0 |= USIPE7 + USIPE6 + USIPE5 + USIMST + USIOE; // Port, SPI Master
	USICTL1 |= USICKPH;                       // flag remains set
	USICKCTL = USIDIV_1 + USISSEL_2;          // /2 SMCLK
	USICTL0 &= ~USISWRST;                     // USI released for operation
	USICNT = USICNT | 0x50;    // 16 bit mode; 16 bit to be transmitted/received
	return;
}

/*
 Name:
 LED_Matrix_Init
 Input:
 nothing
 Output:
 nothing
 Description:
 Initialize the matrix pins and latch.
 Initialize watchdog timer as timer interval.
 */
void LED_Matrix_Init(void) {
	// configure SPI pins and latch
	P1DIR |= DATA_LATCH_PIN | SPI_DATA_OUT_PIN | SPI_CLK_OUT_PIN;

	// set latch pin to inactive
	P1OUT &= ~DATA_LATCH_PIN;

	// using WatchDog Timer as interval timer for Matrix refresh interrupts
	WDTCTL = WDT_MDLY_0_5;    // Set Watchdog Timer interval to 0.5ms
	IE1 |= WDTIE;             // Enable WDT interrupt

	USI_Init();
	return;
}

/*
 Name:
 Set_Matrix
 Input:
 New - array of bytes to be displayed on the matrix
 Count - number of columns to be displayed
 Output:
 nothing
 Description:
 Moving the new data to the Matrix array.
 You can "cut" the picture and display only first <Count> columns.
 */
void Set_Matrix(const unsigned char New[], int Count = 7) {
	unsigned char i;
	for (i = 0; i < Count; i++)
		Matrix[i] = New[i];
	for (i = Count; i < 8; i++)
		Matrix[i] = 0x00;
	return;
}

/*
 Name:
 Set_Matrix_Rotate
 Input:
 New - array of bytes to be displayed on the matrix
 Degree - the way the picture will be rotated (possible values 90, 180, 270; otherwise count as 0)
 Output:
 nothing
 Description:
 Similar to Set_Matrix but with an option to rotate the picture giving you opportunity
 to draw picture as array with a different way.
 */
void Set_Matrix_Rotate(const unsigned char New[], int Degree) {
	unsigned char i, j;
	unsigned char Temp[8], x;
	switch (Degree) {
	case 90:
		for (i = 0; i < 8; i++)
			Temp[i] = 0;

		for (i = 0; i < 8; i++) {
			x = New[i];
			for (j = 0; j < 8; j++) {
				Temp[7 - j] = Temp[7 - j] | ((x & 1) << i);
				x = x >> 1;
			}
		}
		break;

	case 180:
		for (i = 0; i < 8; i++) {
			x = New[i];
			Temp[i] = 0;
			for (j = 0; j < 8; j++) {
				Temp[i] = Temp[i] << 1 | (x & 1);
				x = x >> 1;
			}
		}
		break;

	case 270:
		for (i = 0; i < 8; ++i)
			Temp[i] = 0;

		for (i = 0; i < 8; ++i) {
			x = New[i];
			for (j = 0; j < 8; ++j) {
				Temp[j] |= ((x & 1) << (7 - i));
				x = x >> 1;
			}
		}
		break;

	default:
		for (i = 0; i < 8; ++i)
			Temp[i] = New[i];
		break;
	}

	for (i = 0; i < 8; ++i)
		Matrix[i] = Temp[i];
	return;
}

/*
 Name:
 Write_Matrix
 Input:
 nothing
 Output:
 nothing
 Description:
 Using watchdog timer interrupt to display the picture column by column.
 The column is selected by the <index> and Matrix[index] contains
 the respective bits to be ON.
 */
#pragma vector=WDT_VECTOR
__interrupt void Write_Matrix(void) {
	static unsigned char index = 0;

	P1OUT |= DATA_LATCH_PIN;
	P1OUT &= ~DATA_LATCH_PIN;

	USICTL1 &= ~USIIFG; // Clears the interrupt flag
	USISRH = 1 << index; // Move the index of the column in the high bits of USISR
	USISRL = Matrix[index]; // Move the index of the rows (value of Matrix[index]) in the low bits of USIRS
	USICNT |= 0x10; // 16 bit to write

	++index;
	index &= 7;
}
