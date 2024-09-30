#include <avr/io.h>
#include "joystick.h"

void joystick_test() {
    DDRA = 0;

    while(1) {
        if(PINA & (1 << PA0)) {
            printf("UP\n");
        } else if(PINA & (1 << PA1)) {
            printf("DOWN\n");
        } else if(PINA & (1 << PA2)) {
            printf("LEFT\n");
        } else if(PINA & (1 << PA3)) {
            printf("RIGHT\n");
        } else if(PINA & (1 << PA4)) {
            printf("PRESS\n");
        }
    }
}

int joystick_pos() {

}

enum Direction joystick_dir() {

}

int sliders_pos() {

}