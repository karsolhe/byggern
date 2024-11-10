#include "motor_controller.h"
#include "motor_driver.h"

int motor_position_controller(char joy_percent, int error_sum) {
    uint32_t encoder_value = encoder_read_ch0();
    // if(encoder_value <= 0.0) {
    //     encoder_value = 0.0;
    // } else if(encoder_value >= 2800) {
    //     encoder_value = 2800;
    // }

    double encoder_calib = (((double)encoder_value-1400) * 100) / 1400;

    double error = (double)joy_percent - encoder_calib;


    if(error >= 200) {
        error = 200;
    } else if(error <= -200) {
        error = -200;
    }

    //printf("encoder calib: %f\n\r", encoder_calib);
    printf("error: %f\n\r", error);

    error_sum = error_sum + error;

    double K_p = 0.5;
    double K_i = 0.001;

    double T = 0.001;

    uint8_t I = T * K_i * error_sum;

    double u  = K_p * error + I; // max 100, min 0

    if(u > 100) {
        u = 100;
    } else if(u < 0) {
        u = 0;
    }

    motor_driver_speed(u);  //duty cycle
    return error_sum;
}