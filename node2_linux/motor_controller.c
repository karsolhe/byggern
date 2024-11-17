#include "motor_controller.h"
#include "motor_driver.h"
#include "sam/sam3x/include/component/component_tc.h"
#include "sam/sam3x/include/sam3x8e.h"

volatile int update_controller_flag = 0;
volatile double K_p;
volatile double K_i;

// Initialize timer counter
void timer_counter_init() {
    PMC->PMC_PCER0 |= (1 << ID_TC1);

    TC0->TC_CHANNEL[1].TC_CMR |= TC_CMR_TCCLKS_TIMER_CLOCK4; // Sets clock to 84MHz / 128 = sampling interval 10ms
    TC0->TC_CHANNEL[1].TC_CMR |= TC_CMR_WAVE; // Capture mode is disabled (Waveform mode is enabled
    TC0->TC_CHANNEL[1].TC_CMR |= TC_CMR_WAVSEL_UP_RC; // UP mode with automatic trigger on RC Compare
    TC0->TC_CHANNEL[1].TC_RC |= (84000000/128) * 10/1000; // RC contains the Register C value in real time

    TC0->TC_CHANNEL[1].TC_IER |= TC_IER_CPCS; // Enables the RC Compare Interrupt
    TC0->TC_CHANNEL[1].TC_IMR |= TC_IMR_CPCS; // The RC Compare Interrupt is enabled

    TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;

    NVIC_EnableIRQ(TC1_IRQn);
}

// Handler for timer to update PI controller
void TC1_Handler() {
    if((TC0->TC_CHANNEL[1].TC_SR & TC_SR_CPCS) == TC_SR_CPCS) {
        update_controller_flag = 1;
    }
}

// PI controller for position
Controller motor_position_controller(uint16_t pos_ref, double error_sum) {

    int pos_measured = encoder_read_ch0();

    if(pos_measured <= 0) {
        pos_measured = 0;
    }
    
    double pos_calib = (((double)pos_measured) * 100) / 2800;
    double error = (double)pos_ref - pos_calib;


    //positive e = right negative e = left
    int dir = 1;
    if (error <= 0) {
        dir = 0;
    } else if(error > 0) {
        dir = 1;
    } else { }

    if(fabs(error) < 2) {
        error = 0;
    } 

    error_sum = error_sum + error;

    double T = 0.01;
    double I = T * K_i * fabs(error_sum);
    double u; // Want u between 0 and 0.02

    if(error == 0) {
        u = 0;
    } else {u  = K_p * fabs(error) + I;}

    Controller c = {.u = u, .dir = dir, .error_sum = error_sum};
    return c;
}
