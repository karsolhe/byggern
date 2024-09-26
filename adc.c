#include "adc.h"
#include <avr/io.h>
#include <avr/delay.h>

void adc_init() {
    
    MCUCR |= (1 << SRE);
    SFIOR &= ~(0b111<<XMM0); //Clears the three last bits
    SFIOR |= (1 << XMM2);  //Disables pins used by JTA

    DDRD |= 0b10000;
    TCCR3A |= (1<<WGM31); // Set pin D4 to fast PWM mode
    TCCR3A |= (1<<WGM30);

}

uint8_t adc_read(uint8_t channel) {

}

void pos_calibrate() {

}

// pos_t pos_read(void) {

// }