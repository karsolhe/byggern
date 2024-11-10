#pragma once

#include <stdint.h>
#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/include/component/component_pwm.h"
#include <stdio.h>

uint32_t pwm_get_cprd(uint64_t master_clock, uint16_t prescaler, double period);

uint32_t pwm_get_cdty(uint64_t master_clock, uint16_t prescaler, double duty_cycle);

void pwm_init();

void pwm_duty_cycle_update(double duty_cycle);

void pwm_duty_cycle_update_speed(double duty_cycle);

double pwm_percent_to_duty_cycle(char data);

double pwm_percent_to_duty_cycle_speed(char data);