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

    // uint8_t data[4];

    // data[0] = 'J';
    // data[1] = 'a';
    // data[2] = 'p';
    // data[3] = 'p';


    // CanMsg m_2 = {
    //     .id = 0x01,
    //     .length = 4,
    //     .byte = {data[0], data[1], data[2], data[3]}
    // };

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
            //printf("Message recieved \n\r");
            CanMsg m;
            buffer_get(&m);
            uint8_t id = m.id;
            /*CAN_message sliders;
            sliders.ID = 111;
            sliders.length = 2;
            sliders.data[0] = slide_perc.right;
            sliders.data[1] = slide_perc.left;*/
            //uint32_t encoder_value;
            switch (id)
            {
            case 1:
                //printf("Slider message recieved \n\r");
                //encoder_value = encoder_read_ch0();
                //printf("encoder %d\n\r", encoder_value);
                pwm_duty_cycle_update(pwm_percent_to_duty_cycle(m.byte[0]));
                //printf("Left slider value: %d\n\r", m.byte[1]);
                //printf("Reference: %d\n\r", motor_driver_position_slider(m.byte[1]));

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
                    //printf("Recieved button push\n\r");
                    solenoid_trigger();
                }


                //motor_driver_dir_slider(m.byte[1]);
                //motor_driver_speed_slider(m.byte[1]);
                //printf("Duty cycle: %f\n\r", pwm_percent_to_duty_cycle(m.byte[0]));
                break;
            case 2:
                // motor_driver_dir(m.byte[1]);
                // motor_driver_speed(m.byte[0]);

                // error_sum = motor_position_controller(m.byte[0], error_sum);


                // pwm_duty_cycle_update_speed(pwm_percent_to_duty_cycle(m.byte[0]));
                break;
            case 3:
                printf("Touch button message recieved \n\r");
                
                break;
            default:
                break;
            }
            
            //can_printmsg(m);
        }

        // ADC read

        //uint16_t adc_data = adc_ir_read();
        //printf("adc value: %d\n\r", adc_data);

        printf("Health points: %d\n\r", hp);

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
            printf("Message sent\n\r");
        }

        if(hp <= 0) {
            printf("you lost \n\r");
            break;
        }

        //!  EXERCISE 8
        // uint32_t encoder_value;
        // encoder_value = encoder_read_ch0();

        // printf("encoder %d\n\r", encoder_value);
        // time_spinFor(msecs(100));

    }

    

    
}


