#include <stdint.h>
#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/include/component/component_pio.h"
#include <stdio.h>
#include "sam.h"


void motor_driver_init();

void motor_driver_dir(char data);

void motor_driver_speed(char data);