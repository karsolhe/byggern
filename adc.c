#include "adc.h"
#include <avr/io.h>
#include <avr/delay.h>
#include "address_decoder.h"

#define CHANNEL_NUM 4
#define EXT_MEM ((EXTERNAL_MEMORY*) 0x1000)
#define F_CPU 4915200



void adc_init() {

    DDRD |= (1 << PD4); // Set pin D4 to output
    TCCR3A |= (1<<WGM31); // Set pin D4 to fast PWM mode
    TCCR3A |= (1<<WGM30);
    //TCCR3A |= (1<<COM3A1); // Set compare output mode to clear on compare match
    TCCR3A |= (1<<COM3A0);

    TCCR3B |= (1<<WGM33);
    TCCR3B |= (1<<WGM32); 
    TCCR3B |= (1<<CS30); // Set prescaler to 1

    // ICR3 = 2; 
    // OCR3A = 1; 

    OCR3AH = 0;
    OCR3AL = 0;
    ASSR = 0; 
    

}

uint8_t adc_read(uint8_t channel) {

    volatile char *adc = (char*) 0x1400;

    adc[0] = 0;

    int conv_time = (9 * CHANNEL_NUM * 2)/ F_CPU;

    _delay_us(conv_time);

    uint8_t data;

    for(int i = 0; i <= channel; i++) {
        data = adc[0];
    }
        
    return data;
}

