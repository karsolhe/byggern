#include "uart.h"
#include "latch.h"
#include "SRAM_test.h"
#include "address_decoder.h"
#include "joystick_sliders.h"
#include "adc.h"
#include "oled.h"
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

    // while(1) {
        
        
        //pos_t joy_p = joystick_pos();
        //sliders_t sliders_p = sliders_pos();

        //pos_t pos = pos_read();

        //printf("Joystick_x: %d\n\r", joy_p.x);
        //printf("Joystick_y: %d\n\r", joy_p.y);

        // printf("Joystick_x: %d\n\r", joy_perc.x);
        // printf("Joystick_y: %d\n\r", joy_perc.y);
        //printf("Sliders_left: %d\n\r", sliders_p.left);
        //printf("Sliders_right: %d\n\r", sliders_p.right);
        //printf("Value_x: %d\n\r", pos.x);
        //printf("Value_y: %d\n\r", pos.y);

    //     _delay_ms(1000);
    // }

    //EXERCISE 4

    OLED_init();

    OLED_write_data(0b00000000);
};

