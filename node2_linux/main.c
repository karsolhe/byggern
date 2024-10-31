#include <stdio.h>
#include <stdarg.h>
#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/source/system_sam3x.h"
#include "can.h"


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

    // PMC->PMC_WPMR = 0x504D400; //disables write protect for PMC

    // PMC->PMC_PCER1 |= (PMC_PCER1_PID44); //Enables the corresponding peripheral clock.
    // PMC->PMC_PCER1 |= (PMC_PCER1_PID43);

    // //? kan sjekke status

    // PIOA->PIO_WPMR = 0x50494F00;

    //PIOA->PIO_PDR |= PIO_PDR_P0; //Disables the PIO from controlling the corresponding pin (enables peripheral control of the pin)
    // PIOA->PIO_PDR |= PIO_PDR_P1;

    // PIOA->PIO_ABSR &= ~(1); //Assigns the I/O line to the Peripheral A function.
    // PIOA->PIO_ABSR &= ~(1 << 1);

    

    //Uncomment after including uart above
    uart_init(84000000, 9600);
    // printf("Hello World\n\r");
   

    can_init((CanInit){.brp = 41, .smp = 0, .phase1 = 3, .phase2 = 3, .propag = 3, .sjw = 3}, 1);

    uint8_t data[4];

    data[0] = 'J';
    data[1] = 'a';
    data[2] = 'p';
    data[3] = 'p';


    CanMsg m_2 = (CanMsg) {.id = 0, .length = 4, .byte8 = data};

    

    can_tx(m_2);
}




