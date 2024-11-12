#include <stdint.h>
#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/include/component/component_pio.h"
#include <stdio.h>
#include "encoder.h"
#include <math.h>

typedef struct PID{
    double u;
    int dir;
    double error_sum;
} Controller;

Controller motor_position_controller(uint16_t pos_ref, int error_sum);

