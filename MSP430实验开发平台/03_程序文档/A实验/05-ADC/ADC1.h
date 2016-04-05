#ifndef _ADC_H
#define _ADC_H


#define ADC12_EN do{ADC12CTL0|=ADC12ENC;}while(0)
#define ADC12_START do{ ADC12CTL0|=ADC12SC;}while(0)

extern void Init_ADC(void);

#endif