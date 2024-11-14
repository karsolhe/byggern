#include "solenoid.h"


void solenoid_init() {
    
    PMC->PMC_PCER0 |= (1 << ID_PIOC);

    // Solenoid trigger pin
    PIOC->PIO_PER |= PIO_PER_P15;
    PIOC->PIO_OER |= PIO_OER_P15;
    PIOC->PIO_SODR |= PIO_SODR_P15;
}

void solenoid_trigger() {
    PIOC->PIO_CODR |= PIO_CODR_P15;
    time_spinFor(msecs(25));
    PIOC->PIO_SODR |= PIO_SODR_P15;
}