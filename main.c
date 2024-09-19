#include "uart.h"
#include "latch.h"
#include "SRAM_test.h"

void main() {

    // DDRA = 0b1000; // Setter pin 5 til input

    // while(1) {
    //     PORTA = 0b1000; // Gjør pin 5 høy
    //     _delay_ms(300);
    //     PORTA = 0;
    //     _delay_ms(300);
    // }

    uart_init(MYUBRR);
    
    // uart_test();

    // while(1) {
    //     printf("Hei");
    //     _delay_ms(300);
    // }

    //latch_init();

    //led_test();

    SRAM_init();

    SRAM_test();
} 

