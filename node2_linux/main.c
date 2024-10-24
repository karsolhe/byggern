#include <stdio.h>
#include <stdarg.h>
#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/source/system_sam3x.h"

/*
 * Remember to update the Makefile with the (relative) path to the uart.c file.
 * This starter code will not compile until the UART file has been included in the Makefile. 
 * If you get somewhat cryptic errors referencing functions such as _sbrk, 
 * _close_r, _write_r, _fstat etc, you have most likely not done that correctly.

 * If you get errors such as "arm-none-eabi-gcc: no such file", you may need to reinstall the arm gcc packages using
 * apt or your favorite package manager.
 */
#include "uart.h"

int main()
{
    SystemInit();

    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    //Uncomment after including uart above
    //uart_init(84000000, 9600);
    //printf("Hello World\n\r");

    //PIOB->PIO_WPMR &= ~(1 << PIO_WPMR_WPEN); // Disable write protect by clearing the WPEN bit

    PIOB->PIO_PER |= (1 << PIO_PB13);
    //PIOB->PIO_PDR = 0xFFFFDFFF;
    
    PIOB->PIO_OER |= (1 << PIO_PB13); // Enable output on pin
    // PIOB->PIO_ODR = 0xFFFFDFFF;

    //PIOB->PIO_SODR |= (1 << PIO_PB13); // Set pin P13 high
    PIOB->PIO_CODR |= (1 << PIO_PB13); // clear pin 13

    // PIOB->PIO_PUDR |= (1 << PIO_PB13);

    // PIOB->PIO_OWER |= (1 << PIO_PB13);
    // PIOB->PIO_OWDR = 0xFFFFDFFF;
    
}