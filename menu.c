#include "menu.h"
#include <avr/io.h>
#include <stdint.h>
#include "oled.h"
#include "joystick_sliders.h"
#include <avr/delay.h>

int game_started;

void OLED_create_home_menu() {
    OLED_pos(0, 20);
    OLED_print_string("Ping-pong Game!");
    OLED_pos(2, 30);
    OLED_print_string("Start game");
    OLED_pos(4, 30);
    OLED_print_string("Select difficulty");

};

void OLED_create_difficulty_menu() {
    OLED_pos(0, 20);
    OLED_print_string("Choose Difficulty:");
    OLED_pos(2, 30);
    OLED_print_string("Easy");
    OLED_pos(4, 30);
    OLED_print_string("Medium");
    OLED_pos(6, 30);
    OLED_print_string("Hard");
};

int OLED_navigate_menu() {

    uint8_t joy_button = joystick_button();
    int page = 2;
    OLED_print_arrow(page, 10);

    while(joy_button != 1) {
        joy_button = joystick_button();
        //printf("Joystick button: %d\n\r", joy_button);
        //_delay_ms(500);

        pos_t pos = joystick_percent();
        
        if(pos.y <= 10 & (page >= 0) & (page < 7)) {
            page ++;
            OLED_erase_arrow(page-1, 10);
            OLED_print_arrow(page, 10);
            _delay_ms(1000);
        }

        if(pos.y >= 90 & (page > 0) & (page <= 7)) {
            page --;
            OLED_erase_arrow(page+1, 10);
            OLED_print_arrow(page, 10);
            _delay_ms(1000);
        }
    }

    return page;
};

void OLED_select_menu_item(int page) {
     switch(page) {
        case 0:
            OLED_reset();
            OLED_pos(3, 0);
            OLED_print_string("Troika");
            break;
        case 1:
            OLED_reset();
            OLED_pos(3, 0);
            OLED_print_string("Japp");
            break;
        case 2:
            OLED_reset();
            for(int i = 0; i < 8; i++) {
                OLED_pos(i, 20);
                OLED_print_string("Game started!");
                _delay_ms(1000);
                OLED_reset();
            }

            OLED_print_lives(5);
            game_started = 1;
            // Create life count with hearts
            break;
        case 4:
            OLED_reset();
            OLED_create_difficulty_menu();
            
            break;
    }
}

void OLED_select_difficulty_item(int page) {

}
