#include "menu.h"
#include <avr/io.h>
#include <stdint.h>
#include "oled.h"
#include "joystick_sliders.h"
#include <avr/delay.h>

void OLED_create_menu() {
    OLED_pos(0, 60);
    OLED_print_string("Tab 1");
    OLED_pos(1, 60);
    OLED_print_string("Tab 2");
    OLED_pos(2, 60);
    OLED_print_string("Tab 3");
    OLED_pos(3, 60);
    OLED_print_string("Tab 4");
    OLED_pos(4, 60);
    OLED_print_string("Tab 5");
    OLED_pos(5, 60);
    OLED_print_string("Tab 6");
};

int OLED_navigate_menu() {

    uint8_t joy_button = joystick_button();
    int page = 0;
    OLED_print_arrow(page, 50);

    while(joy_button != 1) {
        joy_button = joystick_button();
        printf("Joystick button: %d\n\r", joy_button);
        _delay_ms(500);

        pos_t pos = joystick_percent();
        
        if(pos.y <= 10 & (page >= 0) & (page < 7)) {
            page ++;
            OLED_erase_arrow(page-1, 50);
            OLED_print_arrow(page, 50);
            _delay_ms(1000);
        }

        if(pos.y >= 90 & (page > 0) & (page <= 7)) {
            page --;
            OLED_erase_arrow(page+1, 50);
            OLED_print_arrow(page, 50);
            _delay_ms(1000);
        }
    }

    return page;
};