#include "memory_map.h"

void memory_init() {
    //DDRD |= (1<<2);
    DDRE |= (1<<1);

    PORTE = 0b10;

    MCUCR |= 0b01000000;

    DDRA = 0b11111111;
}
    

void output_enable() {

}

void latch_enable() {

}

void led_test() {

    PORTA = 0b00000001;
    _delay_ms(1000);
    PORTA = 0b00000010;
    _delay_ms(1000);
    PORTA = 0b00000011;
    _delay_ms(1000);
    PORTA = 0b00000000;
}