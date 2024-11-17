#include "latch.h"

// Initialize latch
void latch_init() {
    DDRE = 0b10; // Set pin on Port E to output

    PORTE = 0b10; // Enable latch, by setting ALE signal

    DDRA = 0b11111111; // Set all pins on Port A to output
}

// Test latch
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