#include "menu.h"
#include <avr/io.h>
#include <stdint.h>
#include "oled.h"
#include "joystick_sliders.h"
#include <avr/delay.h>

int game_started;
int menu;

void menu_create_home_menu() {
    OLED_reset();
    OLED_pos(0, 20);
    OLED_print_string("Ping-pong Game!");
    OLED_pos(2, 30);
    OLED_print_string("Start game");
    OLED_pos(4, 30);
    OLED_print_string("Select difficulty");

};

void menu_create_difficulty_menu() {
    OLED_reset();
    OLED_pos(0, 20);
    OLED_print_string("Choose Difficulty:");
    OLED_pos(2, 30);
    OLED_print_string("Easy");
    OLED_pos(4, 30);
    OLED_print_string("Medium");
    OLED_pos(6, 30);
    OLED_print_string("Hard");
};

int menu_navigate() {

    uint8_t joy_button = joystick_button();
    int page = 0;
    OLED_print_arrow(page, 10);

    // Navigates menu until joystick button is pressed
    while(joy_button != 1) {
        joy_button = joystick_button();

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
    _delay_ms(1000);
    return page;
};

void menu_select_item(int page) {
     switch(page) {
        case 0:
            OLED_reset();
            OLED_pos(3, 0);
            OLED_print_string("Troika");
            _delay_ms(2000);
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
            break;
        case 4:
            OLED_reset();
            menu_create_difficulty_menu();
            menu = 1;
            _delay_ms(1000);
            break;
        default:
            menu = 0;
            break;
    }
}

CAN_message menu_select_difficulty_item(int page) {
    CAN_message difficulty = {};
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
            menu = 0;
            difficulty.ID = 2;
            difficulty.length = 1;
            difficulty.data[0] = 0;
            break;
        case 4:
            menu = 0;
            difficulty.ID = 2;
            difficulty.length = 1;
            difficulty.data[0] = 1;
            break;
        case 6:
            menu = 0;
            difficulty.ID = 2;
            difficulty.length = 1;
            difficulty.data[0] = 2;
            break;
        default:
            menu_create_difficulty_menu();
            break;
    }
    return difficulty;
}
