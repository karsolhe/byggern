#include "address_decoder.h"
#include <avr/io.h>
#include <util/delay.h>

// Test to see if chip select logic works
void address_decoder_test() {
    
    volatile char *oled_c = (char *) 0x1000;
    volatile char *oled_d = (char *) 0x1200;
    volatile char *adc = (char *) 0x1400;
    volatile char *sram = (char *) 0x1800;

    oled_c[0] = 0;
    _delay_ms(5000);
    oled_d[0] = 0;
    _delay_ms(5000);
    adc[0] = 0;
    _delay_ms(5000);
    sram[0] = 0;
    _delay_ms(7000);
};