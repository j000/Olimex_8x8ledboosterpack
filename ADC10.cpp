#include "main.h"
#include "ADC10.h"

/*
 Name:
 ADC10_Init
 Input:
 nothing
 Output:
 nothing
 Description:
 Initialization of the ADC10 Unit with the respective values.
 */
void ADC10_Init(void) {
	// Reference generator On; Multiple Sample and Conversion; Reference selection; ADC - ON.
	ADC10CTL0 = REFON + MSC + SREF_1 + ADC10SHT_3 + ADC10ON;

	// select channel 0; Conversion Sequence - Repeat Singe Channel; Clock Divider - 8; Clock Source selection - SMCLK
	ADC10CTL1 = INCH_0 + CONSEQ_2 + ADC10DIV_7 + ADC10SSEL_3;

	// P1.0 ADC option select
	ADC10AE0 |= 0x01;

	// start continuous convertions
	ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start

	return;
}

/*
 Name:
 ADC10_Calibrate
 Input:
 Count - count of the the measurements to be done
 Output:
 avg - average value of the measurements
 Description
 This function calculate an average value of <count> converts of the ADC10.
 After that value is considered as a "zero" value for the further conversions.
 */
int ADC10_Calibrate(int count) {
	int i;
	long int avg = 0;
	Delay(10000);
	for (i = count; i > 0; --i) {
		Delay(100);
		avg += ADC10MEM;   // accumulate the total value of the measurements
	}
	avg /= count;        // calculating the average
	return (int) avg;
}

/*
 Name:
 ADC10_GetResult
 Input:
 AVG - "Zero" value of the for the ADC10
 Output
 Value - Absolute value of the measured by ADC10 value reffered to AVG
 Description:
 Takes the value from the ADC10.
 */
int ADC10_GetResult(int AVG) {
	int Value;

	Value = ADC10MEM;
	Value -= AVG;
	if (Value < 0)
		Value = -Value;
	return Value;
}
/*
 Name:
 ADC10::Init
 Input:
 nothing
 Output:
 nothing
 Description:
 Initialization of the ADC10 Unit with the respective values.
 */
void ADC10::Init(void) {
	// Reference generator On; Multiple Sample and Conversion; Reference selection; ADC - ON.
	ADC10CTL0 = REFON + MSC + SREF_1 + ADC10SHT_3 + ADC10ON;

	// select channel 0; Conversion Sequence - Repeat Singe Channel; Clock Divider - 8; Clock Source selection - SMCLK
	ADC10CTL1 = INCH_0 + CONSEQ_2 + ADC10DIV_7 + ADC10SSEL_3;

	// P1.0 ADC option select
	ADC10AE0 |= 0x01;

	// start continuous convertions
	ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start

	average = 0;

	return;
}

/*
 Name:
 ADC10::Calibrate
 Input:
 Count - count of the the measurements to be done
 Output:
 avg - average value of the measurements
 Description
 This function calculate an average value of <count> converts of the ADC10.
 After that value is considered as a "zero" value for the further conversions.
 */
void ADC10::Calibrate(int count) {
	int i;
	long unsigned int avg = 0;
	Delay(10000);
	for (i = count; i > 0; --i) {
		Delay(100);
		avg += ADC10MEM;   // accumulate the total value of the measurements
	}
	average = avg / count;        // calculating the average
}

/*
 Name:
 ADC10::GetResult
 Input:
 AVG - "Zero" value of the for the ADC10
 Output
 Value - Absolute value of the measured by ADC10 value reffered to AVG
 Description:
 Takes the value from the ADC10.
 */
int ADC10::GetResult() {
	int Value;

	Value = ADC10MEM;
	Value -= average;
	if (Value < 0)
		Value = 0;        //-Value;
	return Value;
}
