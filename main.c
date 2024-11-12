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

    // while(1) {
    //     printf("Troika");
    //     _delay_ms(300);

    // }
    
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

    joy_cal_pos cal_pos = {0, 0};
    //joystick_calibrate(&cal_pos);
    // printf("Calibrate x %d\n\r", cal_pos.x_offset);
    // printf("Calibrate y %d\n\r", cal_pos.y_offset);


    // while(1) {
    //     pos_t joy_p = joystick_pos(cal_pos);
    //     pos_t joy_perc = joystick_percent(cal_pos);
    //     Direction dir = joystick_dir();
    //     sliders_t sliders_p = sliders_pos();
    //     sliders_t slide_perc = sliders_percent();
    //     uint8_t button = joystick_button();
    //     touch_buttons buttons = touch_button();
    //     uint8_t touch_left = left_touch_button();
    //     uint8_t touch_right = right_touch_button();

        // printf("adc_read: %d\n\r", (uint16_t)adc_read(0));
        // printf("adc_read: %d\n\r", (uint16_t)adc_read(1));
        

        //printf("Joystick_x: %d\n\r", joy_p.x);
        // printf("Joystick_y: %d\n\r", joy_p.y);

        // printf("Joystick_x_perc: %d\n\r", joy_perc.x);
        // printf("Joystick_y_perc: %d\n\r", joy_perc.y);

        // printf("Joystick dir: %d\n\r", dir);

        // printf("Sliders_left: %d\n\r", sliders_p.left);
        // printf("Sliders_right: %d\n\r", sliders_p.right);

        //printf("Sliders_left_perc: %d\n\r", slide_perc.left);
        // printf("Sliders_right_perc: %d\n\r", slide_perc.right);
        
        // printf("Joystick button: %d\n\r", button);

        // printf("Left touch button: %d\n\r", buttons.left);
        // printf("Right touch button: %d\n\r", buttons.right);

        // printf("Left touch button: %d\n\r", touch_left);
        // printf("Right touch button: %d\n\n", touch_right);

    //     _delay_ms(1000);
    // }

    //!EXERCISE 4

    OLED_init();

    OLED_reset();

    //OLED_print_arrow(0, 10);

    //OLED_pos(7, 0);
    //OLED_print_char('b');

    // OLED_create_menu();

    // int menu_item = OLED_navigate_menu();

    // switch(menu_item) {
    //     case 0:
    //         OLED_reset();
    //         OLED_pos(3, 0);
    //         OLED_print_string("Troika");
    //         break;
    //     case 1:
    //         OLED_reset();
    //         OLED_pos(3, 0);
    //         OLED_print_string("Japp");
    //         break;
    //     case 2:
    //         OLED_reset();
    //         OLED_pos(3, 0);
    //         OLED_print_string("Snickers");
    //         break;
    //     case 3:
    //         OLED_reset();
    //         OLED_pos(3, 0);
    //         OLED_print_string("Bounty");
    //         break;
    //     case 4:
    //         OLED_reset();
    //         OLED_pos(3, 0);
    //         OLED_print_string("Mars");
    //         break;
    //     case 5:
    //         OLED_reset();
    //         OLED_pos(3, 0);
    //         OLED_print_string("Melkerull");
    //         break;
    //     default:
    //         OLED_reset();
    //         OLED_pos(3, 0);
    //         OLED_print_string("This is not a menu item..");
    //         break;
    // } 



    //!EXERCISE 5

    //printf("Starting test... \r\n");

    CAN_init();

    // mcp_set_mode(MODE_LOOPBACK);
    // printf("Mode is set \r\n");
    // uint8_t mode = mcp_check_mode();
    // printf("mode: %d\r\n", (mode));

    // CAN_message message = {
    //     1,
    //     8,
    //     "Troika"
    // };

    // CAN_send(&message);
    // CAN_message recieved_message = CAN_recieve();
    // printf("Mottat melding:\r\n");
    // printf("ID: %d\r\n", recieved_message.ID);
    // printf("Length: %d\r\n", recieved_message.length);
    // printf("Data: %s\r\n", recieved_message.data);

    //! EXERCISE 6

    mcp_timing(); //endrer på alle cnf registerene i riktig rekkefølge
    mcp_write(MCP_RXB0CTRL, 0b01100000); //Sets receive buffer 0 to receive all messages)
    mcp_write(MCP_RX_INT, 0b00000011); //Enables both receive buffers to generate an interrupt on message reception
    mcp_set_mode(MODE_NORMAL);
    

    // uint8_t mode = mcp_check_mode();
    // //printf("Mode: %d\r\n", mode);

    CAN_message message = {
        1,
        8,
        "Troika"
    };

    _delay_ms(1000);
    printf("Starting loop\r\n");

    while(1) {

    //CAN_send(&message);
    // //     // _delay_ms(5000);

        if(mcp_read(MCP_CANINTF) & 0b00000001) { //
            CAN_message m = CAN_recieve();
            printf("Message recieved\r\n");
            printf("ID: %d\r\n", m.ID);
            printf("Length: %d\r\n", m.length);
            printf("Data: %s\r\n", m.data);
            mcp_write(MCP_CANINTF, 0b00000001);
        }

        pos_t joy_p = joystick_pos(cal_pos);
        pos_t joy_perc = joystick_percent(cal_pos);
        sliders_t slide_perc = sliders_percent();
        uint8_t button = joystick_button();
        Direction dir = joystick_dir();
        

        char data2[8] = {
            joy_perc.x,
            joy_perc.y
        };

        char data_dir[8] = {
            dir
        };


        CAN_message m_joy_perc_x_dir;
        m_joy_perc_x_dir.ID = 222;
        m_joy_perc_x_dir.length = 2;
        m_joy_perc_x_dir.data[0] = joy_perc.x;
        m_joy_perc_x_dir.data[1] = data_dir[0];

        CAN_message sliders;
        sliders.ID = 111;
        sliders.length = 2;
        sliders.data[0] = slide_perc.right;
        sliders.data[1] = slide_perc.left;

        //CAN_send(&sliders);
        //_delay_ms(5);
        // CAN_send(&message);
        // _delay_ms(100);
        //CAN_send(&m_joy_perc_x_dir);
        CAN_send(&sliders);
        _delay_ms(1);

        //printf("messages sent \n\r");
    
     }
       
};



