#include "motor_driver.h"
#include "encoder.h"
#include "pwm.h"



void motor_driver_init() {
    //phase/dir pin is PC23
    PIOC->PIO_PER = PIO_PER_P23;
    PIOC->PIO_OER = PIO_PDR_P23;

}

/*typedef enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
}Direction;*/

void motor_driver_dir(char data) {
    if(data == 0) {
        PIOC->PIO_SODR = PIO_PER_P23;
    } else if (data == 1) {
        PIOC->PIO_CODR = PIO_PER_P23;
    } else {

    };

}

void motor_driver_speed(char data) {
    pwm_duty_cycle_update_speed(pwm_percent_to_duty_cycle(data));
}
