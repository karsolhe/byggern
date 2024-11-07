#include <stdio.h>
#include <stdarg.h>
#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/source/system_sam3x.h"
#include "can.h"
#include "pwm.h"
#include "ir.h"


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
    

    //Uncomment after including uart above
    uart_init(84000000, 9600);
    
    printf("node 2 initializing\n\r");
    
    can_init((CanInit){.brp = 41, .smp = 0, .phase1 = 3, .phase2 = 3, .propag = 3, .sjw = 3}, 1);

    uint8_t data[4];

    data[0] = 'J';
    data[1] = 'a';
    data[2] = 'p';
    data[3] = 'p';


    CanMsg m_2 = {
        .id = 0x01,
        .length = 4,
        .byte = {data[0], data[1], data[2], data[3]}
    };

    pwm_init();
    adc_init();
   
    

    while(1) {

        if(!buffer_is_empty()) {
            CanMsg m;
            buffer_get(&m);
            uint8_t id = m.id;
            printf("Slider message recieved \n\r");
            pwm_duty_cycle_update(pwm_percent_to_duty_cycle(m.byte[0]));
            printf("Duty cycle: %f\n\r", pwm_percent_to_duty_cycle(m.byte[0]));
            // switch (id)
            // {
            // case 111:
                
            //     break;
            // default:
            //     break;
            // }
            
            //can_printmsg(m);
        }

        uint16_t data = adc_ir_read();
        printf("adc value: %d\n\r", data);

        // double test_0 = pwm_percent_to_duty_cycle(0);
        // double test_50 = pwm_percent_to_duty_cycle(50);
        // double test_100 = pwm_percent_to_duty_cycle(100);
        // printf("Percent to DC test: %f\n\r", test_0);
        // printf("Percent to DC test: %f\n\r", test_50); 
        // printf("Percent to DC test: %f\n\r", test_100);
        
        // pwm_duty_cycle_update(0.0001);

        // for(int i = 0; i < 10000; i++) {};

        // pwm_duty_cycle_update(0.0002);

        // for(int i = 0; i < 10000; i++) {};

        //can_tx(m_2);
        //printf("Message sent\n\r");
        
    }
    

    

    
}




