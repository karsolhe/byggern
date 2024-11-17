#include "uart.h"
#include "latch.h"
#include "SRAM.h"
#include "address_decoder.h"
#include "joystick_sliders.h"
#include "adc.h"
#include "oled.h"
#include "menu.h"
//#include "can.h"

#define F_CPU 4915200 

volatile char *oled_c = (char *) 0x1000;
volatile char *oled_d = (char *) 0x1200;

void main() {
    //!EXERCISE 1

    uart_init(MYUBRR);
    //uart_test();

    //!EXERCISE 2

    latch_init();
    SRAM_init();
    //SRAM_test();
    
    //!EXERCISE 3
    //PB0 and PB1 are used for touch buttons
    DDRB &= ~(1 << PB2); 
    PORTB |= (1 << PB2); // Set pull-up resistor, joystick button

    adc_init();

    //!EXERCISE 4

    OLED_init();
    OLED_reset();

    //!EXERCISE 5

    CAN_init();

    //! EXERCISE 6

    mcp_timing(); // Set timing
    mcp_write(MCP_RXB0CTRL, 0b01100000); //Sets receive buffer 0 to receive all messages
    mcp_write(MCP_RX_INT, 0b00000011); //Enables both receive buffers to generate an interrupt on message reception
    mcp_set_mode(MODE_NORMAL);
    

    //! EXERCISE 7 & 8

    game_started = 0;
    int lives = 5;

    menu_create_home_menu();
    menu = 0;
    CAN_message diff = {.ID = 2, .length = 1, .data[0] = 0};

    // Navigating through menus on OLED
    while(!game_started) {
        int page;
        if(menu == 0) {
            menu_create_home_menu();
            page = menu_navigate();
            menu_select_item(page);
        } else {
            menu_create_difficulty_menu();
            page = menu_navigate();
            diff = menu_select_difficulty_item(page);
        }
    }

    // Send chosen difficulty = parameters for PI controller over CAN
    CAN_send(&diff);
    _delay_ms(1000);

    // Game starts
    while(1) {

        if(mcp_read(MCP_CANINTF) & 0b00000001) { //
            CAN_message m = CAN_recieve();
            lives = m.data[0];

            OLED_print_lives(lives);
            if (lives <= 0) {
                OLED_reset();
                OLED_pos(4, 45);
                OLED_print_string("You Lost :(");
            }
            mcp_write(MCP_CANINTF, 0b00000000); //!
        }

        //pos_t joy_p = joystick_pos();
        pos_t joy_perc = joystick_percent();
        sliders_t slide_perc = sliders_percent();
        uint8_t button = joystick_button();
        Direction dir = joystick_dir();
        touch_buttons buttons = touch_button();
        
        CAN_message sliders;
        sliders.ID = 1;
        sliders.length = 4;
        sliders.data[0] = slide_perc.right;
        sliders.data[1] = slide_perc.left;
        sliders.data[2] = buttons.left;
        sliders.data[3] = buttons.right;  

        CAN_message joystick;
        joystick.ID = 1;
        joystick.length = 4;
        joystick.data[0] = joy_perc.y;
        joystick.data[1] = joy_perc.x;
        joystick.data[2] = buttons.left;
        joystick.data[3] = buttons.right;
        
        CAN_send(&joystick);
     }
       
};



