#include "ir.h"



void adc_init() {
    PMC->PMC_PCR = (ID_ADC << PMC_PCR_PID_Pos);
    PMC->PMC_PCER1 = (1 << (ID_ADC -32)); // good

    ADC->ADC_MR = ADC_MR_FREERUN_ON;
    ADC->ADC_MR = (0b11 << ADC_MR_PRESCAL_Pos);

    ADC->ADC_CR = (1 << 1);

    ADC->ADC_CHER = ADC_CHER_CH0;

}


uint16_t adc_ir_read() {
    uint16_t data;
    data = ADC->ADC_LCDR;
    return data;
}