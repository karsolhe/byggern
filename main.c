#include "uart.h"
#include "latch.h"
#include "SRAM_test.h"
#include "address_decoder.h"
#include "joystick_sliders.h"
#include "adc.h"
#include "oled.h"
#define F_CPU 4915200 


void main() {
    MCUCR |= (1 << SRE);//Enable external memory
    SFIOR &= ~(0b111<<XMM0); //Clears the three last bits
    SFIOR |= (1 << XMM2);  //Disables pins used by JTA

    volatile char *oled_c = (char *) 0x1000;
    volatile char *oled_d = (char *) 0x1200;

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

    

    //SRAM_test();

    //EXERCISE 3

    //joystick_test();

    //adc_init();

    //SRAM_init();

    // while(1) {
        
        
    //     pos_t joy_p = joystick_pos();
    //     sliders_t sliders_p = sliders_pos();

    //     Direction dir = joystick_dir();

    //     //printf("Joystick dir: %d\n\r", dir);

    //     // printf("Joystick_x: %d\n\r", joy_p.x);
    //     // printf("Joystick_y: %d\n\r", joy_p.y);

    //     // printf("Joystick_x: %d\n\r", joy_perc.x);
    //     // printf("Joystick_y: %d\n\r", joy_perc.y);
    //     printf("Sliders_left: %d\n\r", sliders_p.left);
    //     printf("Sliders_right: %d\n\r", sliders_p.right);
    //     // printf("Value_x: %d\n\r", pos.x);
    //     // printf("Value_y: %d\n\r", pos.y);

    //     _delay_ms(1000);
    // }

    //EXERCISE 4

    // DDRB &= ~(1 << PB2); 
    // PORTB |= (1 << PB2); // Set pull-up resistor

    // while(1) {
    //     uint8_t i = joystick_button();
    //     printf("Button: %d\n\r", i);
    //     _delay_ms(1000);

    // }

    OLED_init();
    //OLED_reset();

    // oled_c[0] = 0xb0;
    // oled_c[0] = 0x00;
    // oled_c[0] = 0x10;

    // write_c(0xb0);
    // write_c(0x00);
    // write_c(0x10);

    for(int i = 0; i < 8; i++) {
        oled_c[0] = (0xb0 + i);
        oled_c[0] = (0x00);
        oled_c[0] = (0x10);

        for(int j = 0; j < 128; j++) {
            oled_d[0] = (0b11111111);
        }
    }

    while(1) {
        
        
        //write_d(0b11111111);
        // _delay_ms(1000);
    }

    // while(1) {
    //     address_decoder_test();
    // }

    //oled_c[0] = 0xb0;
    //oled_c[0] = 0x00;
    //oled_c[0] = 0x10;

    //OLED_print_arrow(0, 10);

    //print port a in binary
    //while(1) {
        //oled_d[0] = (0b11111111);
        //write_d(0b11111111);

        // printf("PORTA: ");
        // print_binary(PINA);
        // printf("\n\r");
        // _delay_ms(1000);
    //}

};

