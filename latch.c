#include "latch.h"

void latch_init() {
    DDRE = 0b010;

    PORTE = 0b10;

    DDRA = 0b11111111;
}

void led_test() {

    PORTA = 0b00000001;
    _delay_ms(1000);
    PORTA = 0b00000010;
    _delay_ms(1000);
    PORTA = 0b00000011;

    PORTE = 0b000; //Disable ALE signal

    _delay_ms(1000);
    PORTA = 0b00000000;
}