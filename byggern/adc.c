#include "adc.h"
#include <avr/io.h>
#include <avr/delay.h>

void adc_init() {
    
    MCUCR |= (1 << SRE);
    SFIOR &= ~(0b111<<XMM0); //Clears the three last bits
    SFIOR |= (1 << XMM2);  //Disables pins used by JTA

    DDRD |= (1 << PD4); // Set pin D4 to output
    TCCR3A |= (1<<WGM31); // Set pin D4 to fast PWM mode
    TCCR3A |= (1<<WGM30);
    //TCCR3A |= (1<<COM3A1); // Set compare output mode to clear on compare match
    TCCR3A |= (1<<COM3A0);

    TCCR3B |= (1<<WGM33);
    TCCR3B |= (1<<WGM32); 
    TCCR3B |= (1<<CS30); // Set prescaler to 1

    OCR3AH = 0;
    OCR3AL = 0;
    ASSR = 0; 
    

}

uint8_t adc_read(uint8_t channel) {

    int conv_time = (9 * CHANNEL_NUM * 2)/ F_CPU;

    _delay_ms(conv_time); // Wait for conversion

}

void pos_calibrate() {

}

// pos_t pos_read(void) {

// }