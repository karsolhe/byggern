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

void motor_driver_dir_slider(char data) {
    if(data < 50) {
        PIOC->PIO_SODR = PIO_PER_P23;
    } else {
        PIOC->PIO_CODR = PIO_PER_P23;
    };
}

// Sets motor speed using pwm on channel 0 from joystick
void motor_driver_speed(char data) {
    pwm_duty_cycle_update_speed(pwm_percent_to_duty_cycle(data));
}

// Sets motor speed using pwm on channel 0 from slider
void motor_driver_speed_slider(char data) {
    if(data < 50) {
        pwm_duty_cycle_update_speed(pwm_percent_to_duty_cycle(100-2*data));
    } else if(data > 50) {
        data = (data - 50) * 100 / (100 - 50);
        pwm_duty_cycle_update_speed(pwm_percent_to_duty_cycle(data));
    } else if(data == 50) {
        pwm_duty_cycle_update_speed(pwm_percent_to_duty_cycle(0));
    }
}

// Converts slider percent to encoder scale
uint16_t motor_driver_position_slider(char data) {
    uint16_t new = 0 + ((data - 0) * (2800 -0)) / (100);
    return new;
}
