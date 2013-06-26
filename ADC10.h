#ifndef ADC10_H
#define ADC10_H

#define MIC_VCC_PIN BIT0 // P1.0
#define MIC_ANIN_PIN BIT3 // P1.3

class ADC10 {
	int average;
public:
	void Init(void);
	void Calibrate(/*int count*/);
	int GetResult(void);
};

void ADC10_Init(void);

int ADC10_Calibrate(/*int count*/);

int ADC10_GetResult(int AVG);

#endif
