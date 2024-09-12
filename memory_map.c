#include "memory_map.h"

void memory_init() {
    DDRD |= (1<<2);
    DDRE |= (1<<1);

    MCUCR |= (1<<7);

    DDRA = 0b111;

}

void output_enable() {

}

void latch_enable() {

}

void led_test() {

    PORTE |= (1<<1);

    while(1) {
        PORTA = 0b111;
        _delay_ms(300);
        PORTA = 0;
        _delay_ms(300);
    }
}