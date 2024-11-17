#include "uart.h" 

// Initalize UART
void uart_init(unsigned int ubrr) {
    UBRR0L = (unsigned char)ubrr; 
    UBRR0H = (unsigned char)(ubrr>>8);
    
    UCSR0B = (1<<RXEN0) | (1<<TXEN0); //Enable receiver, enable transmitter
    UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00); // 8 data bit, 2 stop bit

    fdevopen(uart_send, uart_receive);
}

// Send data, enables printf
int uart_send(unsigned char data, FILE * file) {

    while(!(UCSR0A & (1<<UDRE0))); // While transfer buffer is not empty
    UDR0 = data;

    return 0;

}

// Recieves data, enables printf
int uart_receive(FILE * file) {

    while(!(UCSR0A & (1<<RXC0))); // While recieve buffer is empty
    return UDR0;

}

// void uart_send(unsigned char data) {

//     while(!(UCSR0A & (1<<UDRE0))); 
//     UDR0 = data;

// }

// unsigned char uart_receive(void) {

//     while(!(UCSR0A & (1<<RXC0))); 
//     return UDR0;

// }

// Test for UART
// void uart_test() {
//     while(1) {
//         // unsigned char received_data = uart_receive();
//         // uart_send(received_data);
//         uart_send('a');
//         _delay_ms(300);
//     }
// }