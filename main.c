#include "uart.h"
#include "latch.h"
#include "SRAM.h"
#include "address_decoder.h"
#include "joystick_sliders.h"
#include "adc.h"
#include "oled.h"
#include "menu.h"
#include "can.h"
#define F_CPU 4915200 



volatile char *oled_c = (char *) 0x1000;
volatile char *oled_d = (char *) 0x1200;

void main() {
    //!EXERCISE 1

    // DDRA = 0b1000; // Setter pin 5 til input

    // while(1) {
    //     PORTA = 0b1000; // Gjør pin 5 høy
    //     _delay_ms(300);
    //     PORTA = 0;
    //     _delay_ms(300);
    // }

    uart_init(MYUBRR);

    while(1) {
        printf("Troika");
        _delay_ms(300);

    }
    
    //uart_test();

    //!EXERCISE 2

    latch_init();
    // led_test();

    
    SRAM_init();
    //SRAM_test();

    // while (1)
    // {
    //     address_decoder_test();
    // }
    

    //!EXERCISE 3
    //PB0 and PB1 are used for touch buttons
    DDRB &= ~(1 << PB2); 
    PORTB |= (1 << PB2); // Set pull-up resistor, joystick button

    //init touch button pins?
    // DDRB &= ~(1 << PB3); 
    // PORTB |= (1 << PB3);

    // DDRB &= ~(1 << PB1); 
    // PORTB |= (1 << PB1)    OLED_print_arrow(0, 40);; 



    adc_init();


    // while(1) {
        
    //     pos_t joy_p = joystick_pos();
    //     pos_t joy_perc = joystick_percent();
    //     Direction dir = joystick_dir();
    //     sliders_t sliders_p = sliders_pos();
    //     sliders_t slide_perc = sliders_percent();
    //     uint8_t button = joystick_button();
    //     touch_buttons buttons = touch_button();
    //     uint8_t touch_left = left_touch_button();
    //     uint8_t touch_right = right_touch_button();
        

    //     printf("Joystick_x: %d\n\r", joy_p.x);
    //     printf("Joystick_y: %d\n\r", joy_p.y);

        // printf("Joystick_x: %d\n\r", joy_perc.x);
        // printf("Joystick_y: %d\n\r", joy_perc.y);

        //printf("Joystick dir: %d\n\r", dir);

        //printf("Sliders_left: %d\n\r", sliders_p.left);
        //printf("Sliders_right: %d\n\r", sliders_p.right);

        //printf("Sliders_left_perc: %d\n\r", slide_perc.left);
        //printf("Sliders_right_perc: %d\n\r", slide_perc.right);
        
        //printf("Joystick button: %d\n\r", button);

        // printf("Left touch button: %d\n\r", buttons.left);
        // printf("Right touch button: %d\n\r", buttons.right);

        //printf("Left touch button: %d\n\r", touch_left);
        //printf("Right touch button: %d\n\n", touch_right);

    //     _delay_ms(1000);
    //}

    //!EXERCISE 4

    OLED_init();

    OLED_reset();

    //OLED_print_arrow(0, 10);

    //OLED_pos(7, 0);
    //OLED_print_char('b');

    OLED_create_menu();

    int menu_item = OLED_navigate_menu();

    switch(menu_item) {
        case 0:
            OLED_reset();
            OLED_print_char('a');
            break;
        case 1:
            OLED_reset();
            OLED_print_char('a');
            break;
        case 2:
            OLED_reset();
            OLED_print_char('b');
            break;
        case 3:
            OLED_reset();
            OLED_print_char('c');
            break;
        default:
            OLED_reset();
            OLED_print_char('k');
            break;
    } 



    //!EXERCISE 5

    // printf("Starting test...");
    // CAN_init();

    // //kanskje config ting

    // mcp_set_mode(MODE_LOOPBACK);
    // uint8_t mode = mcp_check_mode();
    // printf(mode);

    
    // CAN_message message = {};
    // message.ID = 0b00000000000;
    // message.length = 8;
    // for (int i; i < message.length; i++) {
    //     message.data[i] = 0b10101010;
    // }

    

    // CAN_send(0, &message);

    // CAN_message recieved_message= CAN_recieve();

    //  for (int i; i < recieved_message.length; i++) {
    //     printf(recieved_message.data[i]);
    // }
    
};

