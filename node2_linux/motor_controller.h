#include <stdint.h>
#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/include/component/component_pio.h"
#include <stdio.h>
#include "encoder.h"
#include <math.h>
#include "pwm.h"

extern volatile int update_controller_flag;
extern volatile double K_p;
extern volatile double K_i; 

void timer_counter_init();

typedef struct PID{
    double u;
    int dir;
    double error_sum;
} Controller;

Controller motor_position_controller(uint16_t pos_ref, double error_sum);

