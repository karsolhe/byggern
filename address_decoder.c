#include "address_decoder.h"
#include <avr/io.h>
#include <util/delay.h>

void address_decoder_test() {
    DDRC = (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3);
    
    PORTC = 0b1000; // SRAM
    _delay_ms(5000);
    PORTC = 0b1111; // SRAM
    _delay_ms(5000);
    PORTC = 0b0100; // ADC
    _delay_ms(5000);
    PORTC = 0b0101; // ADC
    _delay_ms(5000);
    PORTC = 0b1111; // SRAM
    _delay_ms(5000);
    PORTC = 0b0000; // OLED
    _delay_ms(5000);
    PORTC = 0b0011; // OLED
};