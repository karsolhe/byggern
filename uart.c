#include "uart.h"

void uart_init(unsigned int ubrr) {
    UBRR0L = (unsigned char)ubrr;
    UBRR0H = (unsigned char)(ubrr>>8);
    
    UCSR0B = (1<<RXEN0) | (1<<TXEN0); //Enable receiver and transmitter
    UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00); //Set frame format: 8 data bit, 2 stop bit

    fdevopen(uart_send, uart_receive);
}

void uart_send(unsigned char data, FILE * file) {

    while(!(UCSR0A & (1<<UDRE0))); //Wait for empty transmit buffer
    UDR0 = data;

}

unsigned char uart_receive(FILE * file) {

    while(!(UCSR0A & (1<<RXC0))); //Wait till data is received
    return UDR0;

}

// void uart_test() {
//     //uart_send('A');
//     while(1) {
//         unsigned char received_data = uart_receive();
//         uart_send(received_data);
//         // uart_send('a');
//         // _delay_ms(300);
//     }
// }