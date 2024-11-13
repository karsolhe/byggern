#include "solenoid.h"


void solenoid_init() {
    // Created 3.3V output source to relay
    PIOC->PIO_PER |= PIO_PER_P17;
    PIOC->PIO_OER |= PIO_OER_P17;
    PIOC->PIO_SODR |= PIO_SODR_P17;

    // Solenoid trigger pin
    PIOC->PIO_PER |= PIO_PER_P15;
    PIOC->PIO_OER |= PIO_OER_P15;
    PIOC->PIO_SODR |= PIO_SODR_P15;
}

void solenoid_trigger() {
    PIOC->PIO_CODR |= PIO_CODR_P15;
    PIOC->PIO_SODR |= PIO_SODR_P15;
}