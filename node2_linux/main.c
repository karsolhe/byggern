#include <stdio.h>
#include <stdarg.h>
//#include <threads.h>
#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/source/system_sam3x.h"
#include "can.h"
#include "pwm.h"
#include "adc.h"
#include "ir.h"
#include "time.h"
#include "encoder.h"
#include "motor_driver.h"
#include "motor_controller.h"
#include "solenoid.h"


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
    uart_init(84000000, 9600);
    
    can_init((CanInit){.brp = 41, .smp = 0, .phase1 = 3, .phase2 = 3, .propag = 3, .sjw = 3}, 1);

    pwm_init();
    adc_init();
    encoder_init();
    motor_driver_init();
    solenoid_init();
    timer_counter_init();
    
    int hp = 5;
    time_spinFor(msecs(10));

    double error_s = 0;
    double u = 0;
    int dir = 1;

    while(1) {
        if(!buffer_is_empty()) {
            CanMsg m;
            buffer_get(&m);
            uint8_t id = m.id;
            switch (id)
            {
            case 1:
                pwm_duty_cycle_update(pwm_percent_to_duty_cycle(m.byte[0]));

                if(update_controller_flag == 1) {
                    update_controller_flag = 0;
                    Controller c = motor_position_controller(m.byte[1], error_s);
                    error_s = c.error_sum;
                    u = c.u;
                    dir = c.dir;
                    motor_driver_dir(dir);
                    pwm_duty_cycle_update_speed(u);
                }

                if(m.byte[2] == 1 || m.byte[3] == 1) {
                    solenoid_trigger();
                }
                break;
            case 2:
                switch(m.byte[0])
                {
                case 0:
                    K_p = 0.00017;
                    K_i = 0.00009;
                    break;
                case 1:
                    K_p = 0.00001;
                    K_i = 0.00001;
                    break;
                case 2:
                    K_p = 0.015;
                    K_i = 0.00001;
                    break;
                default:
                    K_p = 0.00017;
                    K_i = 0.00009;
                    break;
                }
                break;
            case 3:
                printf("Wrong ID\n\r");
                
                break;
            default:
                break;
            }
        }
        
        int lost_life = ir_point_counter(&hp);
        if(lost_life == 1){  

            uint8_t data[1];
            data[0] = hp;


            CanMsg m = {
                .id = 1,
                .length = 1,
                .byte = {data[0]},
            };

            can_tx(m);
            time_spinFor(msecs(200));
        }

        if(hp <= 0) {
            break;
        }
    } 
}


