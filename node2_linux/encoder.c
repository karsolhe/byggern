#include "encoder.h"



void encoder_init() {
    
    PMC->PMC_PCER1 |= (1 << (ID_TC6 -32));
    //PMC->PMC_PCER0 = (1 << (ID_TC2));

    PIOC->PIO_PDR |= PIO_PDR_P25;
    PIOC->PIO_PDR |= PIO_PDR_P26;
    PIOC->PIO_ABSR |= PIO_ABSR_P25; //select peripheral B
    PIOC->PIO_ABSR |= PIO_ABSR_P26;

    TC2->TC_WPMR |= 0x54494D00;
    TC2->TC_BMR = TC_BMR_POSEN | TC_BMR_QDEN;  //Enables the position measure on channel 0 and 1, Enables the QDEC
    TC2->TC_CHANNEL[0].TC_CMR |= TC_CMR_TCCLKS_XC0 | TC_CMR_ETRGEDG_RISING | TC_CMR_ABETRG; //clock selected: XC0, trigger set on rising edge, enable AB trigger
 

    TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;

    //printf("Status: %x\n\r", TC2->TC_CHANNEL[0].TC_SR);
}

int encoder_read_ch0() {
    return TC2->TC_CHANNEL[0].TC_CV;
}

