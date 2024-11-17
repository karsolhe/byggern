#include "pwm.h"
#include "sam/sam3x/include/component/component_pio.h"
#include "sam/sam3x/include/component/component_pwm.h"

// Set PWM period
uint32_t pwm_get_cprd(uint64_t master_clock, uint16_t prescaler, double period){
    uint32_t bit_time = master_clock/(prescaler); 
    return period * bit_time;
}

// Set PWM duty cycle
uint32_t pwm_get_cdty(uint64_t master_clock, uint16_t prescaler, double duty_cycle){
    uint32_t bit_time =master_clock/(prescaler); 
    return duty_cycle * bit_time;
}

// Initialize PWM
void pwm_init() {
    
    PMC->PMC_PCR = (ID_PWM << PMC_PCR_PID_Pos);
    PMC->PMC_PCER1 = (1 << (ID_PWM -32)); 

    PIOB->PIO_OER = PIO_OER_P13;
    PIOB->PIO_PDR = PIO_PDR_P13; // Pin 13 enable peripheral
    PIOB->PIO_ABSR |= PIO_ABSR_P13; // Select peripheral B

    // For the motor_driver PWM
    PIOB->PIO_OER = PIO_OER_P12;
    PIOB->PIO_PDR = PIO_PDR_P12; // Pin 12 enable peripheral
    PIOB->PIO_ABSR |= PIO_ABSR_P12; // Select peripheral B


    PWM->PWM_DIS = PWM_DIS_CHID1 | PWM_DIS_CHID0; // Disables channel 1
    while((PWM->PWM_SR & (1<<1)));

    // First PWM channel for servo
    PWM->PWM_CLK = ((1<<16 ) | 1); 
    PWM->PWM_CH_NUM[1].PWM_CMR = 0b0101; //PWM Channel Mode Register, sets MCK as clock for channel 0
    PWM->PWM_CH_NUM[1].PWM_CMR &= ~(1<<8); //0 = The period is left aligned, vil ha left aligned
    PWM->PWM_CH_NUM[1].PWM_CMR |= PWM_CMR_CPOL; // 1 = The OCx output waveform (output from the comparator) starts at a high level.

    // Second PWM channel, for encoder
    PWM->PWM_CH_NUM[0].PWM_CMR = 0b0101; //PWM Channel Mode Register, sets MCK as clock for channel 0
    PWM->PWM_CH_NUM[0].PWM_CMR &= ~(1<<8); //0 = The period is left aligned, vil ha left aligned
    PWM->PWM_CH_NUM[0].PWM_CMR |= PWM_CMR_CPOL; // 1 = The OCx output waveform (output from the comparator) starts at a high level.

    // Select period and duty cycle for servo
    PWM->PWM_CH_NUM[1].PWM_CPRD = pwm_get_cprd(84000000, 32, 0.02);
    PWM->PWM_CH_NUM[1].PWM_CDTY = pwm_get_cdty(84000000, 32, 0.0015);

    // Select period and duty cycle for encoder
    PWM->PWM_CH_NUM[0].PWM_CPRD = pwm_get_cprd(84000000, 32, 0.02);
    PWM->PWM_CH_NUM[0].PWM_CDTY = pwm_get_cdty(84000000, 32, 0.0015);

    PWM->PWM_ENA = PWM_ENA_CHID1 | PWM_ENA_CHID0;  // PWM Enable Register, enable channel 1
    while(!(PWM->PWM_SR & (1<<1)));

}

// Update duty cycle for servo
void pwm_duty_cycle_update(double duty_cycle) {
    if(duty_cycle < 0.0009 || duty_cycle > 0.0021) {
        printf("Duty cycle ut of range \n\r");
    } else {
        uint32_t cdtyupd = pwm_get_cdty(84000000, 32, duty_cycle);
        PWM->PWM_CH_NUM[1].PWM_CDTYUPD = cdtyupd;
    }
    
}

// Update duty cycle for encoder
void pwm_duty_cycle_update_speed(double duty_cycle) {

    if(duty_cycle >= 0.019) { // før: 0.019
        duty_cycle = 0.019;
    }
    uint32_t cdtyupd = pwm_get_cdty(84000000, 32, duty_cycle);
    PWM->PWM_CH_NUM[0].PWM_CDTYUPD = cdtyupd;
}

// Convert percent to duty cycle for servo
double pwm_percent_to_duty_cycle(char data) {
    if(data > 100) {data=100;}
    if(data < 0) {data=0;}
    double duty_cycle;
    duty_cycle = 0.0009 + (((double)data * (0.0021 - 0.0009))/(100));
    return duty_cycle;
}

// Convert percent to duty cycle for encoder
double pwm_percent_to_duty_cycle_speed(char data) {
    if(data > 100) {data=100;}
    if(data < 0) {data=0;}
    double duty_cycle;
    duty_cycle = 0.0009 + (((double)data * (0.01 - 0.0009))/(100));
    return duty_cycle;
}

