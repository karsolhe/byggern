#include "encoder.h"
#include "sam/sam3x/include/component/component_tc.h"


void encoder_init() {
    PIOC->PIO_PDR |= PIO_PDR_P25;
    PIOC->PIO_PDR |= PIO_PDR_P26;
    PIOC->PIO_ABSR |= PIO_ABSR_P25; //select peripheral B
    PIOC->PIO_ABSR |= PIO_ABSR_P26;

    PMC->PMC_PCR = (ID_TC2 << PMC_PCR_PID_Pos);
    PMC->PMC_PCER0 = (1 << (ID_TC2));

    TC2->TC_BMR |= TC_BMR_POSEN;
    TC2->TC_BMR |= TC_BMR_QDEN;
    
    REG_TC2_CMR0 = TC_CMR_TCCLKS_XC0;
    REG_TC2_CMR1 = TC_CMR_TCCLKS_XC0;

    REG_TC2_CMR0 = TC_CMR_ABETRG;
    REG_TC2_CMR1 = TC_CMR_ABETRG;

    REG_TC2_CMR0 = TC_CMR_ETRGEDG_RISING;
    REG_TC2_CMR1 = TC_CMR_ETRGEDG_RISING;

    REG_TC2_CCR0 = TC_CCR_CLKEN;
    REG_TC2_CCR1 = TC_CCR_CLKEN;

    REG_TC2_CCR0 = TC_CCR_SWTRG;
    REG_TC2_CCR1 = TC_CCR_SWTRG;
}


uint32_t encoder_read() {
    return REG_TC2_CV0;
}