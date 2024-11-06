#include "pwm.h"

void pwm_init() {
    PWM->PWM_WPCR = PWM_WPCR_WPKEY(0x50574D); // Enable writing to registers, key er riktig, resten av bits i samme register kan nå også skrives til
    //skriv bits i PMW_WPCR for å disable write protection

    //set clock to 50 MHz
    PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(20); // Set clock to 50MHz

    PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42); // Set clock to 1MHz
    PWM->PWM_ENA = PWM_ENA_CHID0; // Enable channel 0

    PWM->PWM_CMR0 = PWM_CMR_CPRE_CLKA; // Set clock source to CLKA

    PWM->PWM_IER1 = PWM_IER1_CHID0; // Enable interrupt for channel 0 (Counter Event on Channel x Interrupt Enable)
    // NVIC_EnableIRQ(ID_PWM); // Enable interrupt in NVIC //TODO: Uncomment when PWM interrupt is implemented //ane ikke ka d her e, kom av sæ sjøl
}