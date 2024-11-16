#include "adc.h"


void adc_init() {
    PMC->PMC_PCR = (ID_ADC << PMC_PCR_PID_Pos);
    PMC->PMC_PCER1 = (1 << (ID_ADC -32)); // good

    ADC->ADC_MR |= ADC_MR_FREERUN_ON;
    ADC->ADC_MR |= ADC_MR_PRESCAL(41); //ADCClock 1 MHz
    ADC->ADC_MR |= ADC_MR_TRACKTIM(2);
    ADC->ADC_MR |= ADC_MR_TRANSFER(0);

    ADC->ADC_CR = ADC_CR_START; //START conversion

    ADC->ADC_CHER = ADC_CHER_CH2; //enable channel 0

}


uint16_t adc_ir_read() {
    uint16_t data;
    data = ADC->ADC_LCDR; //last converted data register
    return data;
}