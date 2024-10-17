#include <avr/io.h>
#include "joystick_sliders.h"
#include "adc.h"

void joystick_calibrate() {

}

pos_t joystick_pos() {
    pos_t pos = {0, 0};
    pos.x = adc_read(0);
    pos.y = adc_read(1);
    return pos;
}

pos_t joystick_percent() {
    pos_t pos = joystick_pos();
    pos.x = (pos.x * 100) / 255;
    pos.y = (pos.y * 100) / 255;
    return pos;
}

uint8_t joystick_button() {
    return (PINB & (1 << PB2)) ? 0 : 1;
}

touch_buttons touch_button() {
    touch_buttons buttons = {0, 0};
    buttons.left = (PINB & (1 << PB3)) ? 1 : 0;
    buttons.right = (PINB & (1 << PB1)) ? 1 : 0;
    return buttons;
}

uint8_t left_touch_button() {
    return (PINB & (1 << PB3)) ? 1 : 0;
}

uint8_t right_touch_button() {
    return (PINB & (1 << PB1)) ? 1 : 0;
}


Direction joystick_dir() {
    Direction dir = NEUTRAL;

    pos_t pos = joystick_pos();

    if(pos.x < 100) {
        dir = LEFT;
    } else if(pos.x > 200) {
        dir = RIGHT;
    } else if(pos.y < 100) {
        dir = DOWN;
    } else if(pos.y > 200) {
        dir = UP;
    } else {
        dir = NEUTRAL;
    }

    return dir;
}

sliders_t sliders_pos() {
    sliders_t pos_sliders = {0, 0};
    pos_sliders.right = adc_read(2);
    pos_sliders.left = adc_read(3);
    return pos_sliders;
}

sliders_t sliders_percent() {
    sliders_t pos_sliders = sliders_pos();
    pos_sliders.right = (pos_sliders.right * 100) / 255;
    pos_sliders.left = (pos_sliders.left * 100) / 255;
    return pos_sliders;
}