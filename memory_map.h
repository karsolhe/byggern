#define F_CPU 4915200 
#include <avr/io.h>
#include <avr/delay.h>

void memory_init();

void output_enable();

void latch_enable();

void led_test();