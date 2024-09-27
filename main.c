#include "uart.h"
#include "latch.h"
#include "SRAM_test.h"
#include "address_decoder.h"
#include "joystick.h"
#include "adc.h"
#define F_CPU 4915200 

void main() {

    //EXERCISE 1

    // DDRA = 0b1000; // Setter pin 5 til input

    // while(1) {
    //     PORTA = 0b1000; // Gjør pin 5 høy
    //     _delay_ms(300);
    //     PORTA = 0;
    //     _delay_ms(300);
    // }

    uart_init(MYUBRR);
    
    // uart_test();

    //EXERCISE 2

    //latch_init();

    //led_test();

    // SRAM_init();

    // SRAM_test();

    //address_decoder_test();

    //EXERCISE 3

    //joystick_test();

    adc_init();


    while(1) {
        volatile char *adc = (char*) 0x1400;
        adc[0] = 0b00000001;

        _delay_ms(5);

        uint8_t value = adc[0];
        printf("Value: %d\n", value);
        _delay_ms(1000);
    }
} 

