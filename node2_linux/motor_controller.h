#include <stdint.h>
#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/include/component/component_pio.h"
#include <stdio.h>
#include "encoder.h"

int motor_position_controller(char joy_percent, int error_sum);