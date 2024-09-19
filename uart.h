#define F_CPU 4915200 
#include <avr/io.h>
#include <avr/delay.h>
#include <stdio.h>


#define BAUDRATE 9600
#define MYUBRR (F_CPU/16/BAUDRATE) - 1

void uart_init(unsigned int ubrr);

int uart_send(unsigned char data, FILE * file);

int uart_receive(FILE * file);

// void uart_send(unsigned char data);

// unsigned char uart_receive(void);

void uart_test();