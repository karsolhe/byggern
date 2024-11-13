#include "motor_controller.h"
#include "motor_driver.h"

Controller motor_position_controller(uint16_t pos_ref, int error_sum) {
    uint32_t pos_measured = encoder_read_ch0();
    // if(encoder_value <= 0.0) {
    //     encoder_value = 0.0;
    // } else if(encoder_value >= 2800) {
    //     encoder_value = 2800;
    // }
    if(pos_measured > 2800) {
        pos_measured = 2800;
    } else if (pos_measured < 0) {
        pos_measured = 0;
    }
    
    double pos_calib = (((double)pos_measured) * 100) / 2800;

    double error = (double)pos_ref - pos_calib;

    printf("Error %f\n\r", error);
    //printf("pos_ref: %d\n\r", pos_ref);
    //printf("pos_measured: %d\n\r", pos_measured);

    //positiv e = høyre, negativ e = venstre
    int dir = 1;
    if (error <= 0) {
        dir = 0;
    } else if(error > 0) {
        dir = 1;
    } else { }


    if(fabs(error) < 5) {
        error = 0;
    } 

    error_sum = error_sum + error;

    double K_p = 0.05;
    double K_i = 0.01;

    double T = 0.01;

    double I = T * K_i * error_sum;

    printf("Integral: %f\n\r", I);

    double u; // Want u between 0 and 0.02

    if(error == 0) {
        u = 0;
    } else {u  = K_p * fabs(error) + I;}
     

    printf("u: %f\n\r", u);

    Controller c = {.u = u, .dir = dir, .error_sum = error_sum};
    return c;
}
