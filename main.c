#include "uart.h"
#include "memory_map.h"

void main() {

    // DDRA = 0x20; // Setter pin 5 til input

    // while(1) {
    //     PORTA = 0x20; // Gjør pin 5 høy
    //     _delay_ms(300);
    //     PORTA = 0;
    //     _delay_ms(300);
    // }

    // uart_init(MYUBRR);
    // uart_test();

    // while(1) {
    //     printf("Hei");
    //     _delay_ms(300);
    // }

    memory_init();

    led_test();

} 

