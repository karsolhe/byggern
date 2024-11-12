#include <stdint.h>
#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/include/component/component_pio.h"
#include <stdio.h>
#include "sam.h"

void motor_driver_init();

void motor_driver_dir(char data);

void motor_driver_dir_slider(char data);

void motor_driver_speed(char data);

void motor_driver_speed_slider(char data);

uint16_t motor_driver_position_slider(char data);