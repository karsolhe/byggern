#include "pwm.h"
#include "sam/sam3x/include/component/component_pio.h"
#include "sam/sam3x/include/component/component_pwm.h"




uint32_t pwm_get_cprd(uint64_t master_clock, uint16_t prescaler, double period){
    uint32_t bit_time = master_clock/(prescaler); 
    return period * bit_time;
}

uint32_t pwm_get_cdty(uint64_t master_clock, uint16_t prescaler, double duty_cycle){
    uint32_t bit_time =master_clock/(prescaler); 
    return duty_cycle * bit_time;
}


void pwm_init() {
    
    PMC->PMC_PCR = (ID_PWM << PMC_PCR_PID_Pos);
    PMC->PMC_PCER1 = (1 << (ID_PWM -32)); 

    PIOB->PIO_OER = PIO_OER_P13;
    PIOB->PIO_PDR = PIO_PDR_P13; //pin 13 enable peripheral
    PIOB->PIO_ABSR |= PIO_ABSR_P13; //select peripheral B

    //for the motor_driver PWM
    PIOB->PIO_OER = PIO_OER_P12;
    PIOB->PIO_PDR = PIO_PDR_P12; //pin 12 enable peripheral
    PIOB->PIO_ABSR |= PIO_ABSR_P12; //select peripheral B


    PWM->PWM_DIS = PWM_DIS_CHID1 | PWM_DIS_CHID0;//disables channel 1
    while((PWM->PWM_SR & (1<<1)));
    printf("pwm disabled\n\r");

    PWM->PWM_CLK = ((1<<16 ) | 1); 
    PWM->PWM_CH_NUM[1].PWM_CMR = 0b0101; //PWM Channel Mode Register, sets MCK as clock for channel 0
    PWM->PWM_CH_NUM[1].PWM_CMR &= ~(1<<8); //0 = The period is left aligned, vil ha left aligned
    PWM->PWM_CH_NUM[1].PWM_CMR |= PWM_CMR_CPOL; // 1 = The OCx output waveform (output from the comparator) starts at a high level.

    PWM->PWM_CH_NUM[0].PWM_CMR = 0b0101; //PWM Channel Mode Register, sets MCK as clock for channel 0
    PWM->PWM_CH_NUM[0].PWM_CMR &= ~(1<<8); //0 = The period is left aligned, vil ha left aligned
    PWM->PWM_CH_NUM[0].PWM_CMR |= PWM_CMR_CPOL; // 1 = The OCx output waveform (output from the comparator) starts at a high level.

   
    PWM->PWM_CH_NUM[1].PWM_CPRD = pwm_get_cprd(84000000, 32, 0.02);
    PWM->PWM_CH_NUM[1].PWM_CDTY = pwm_get_cdty(84000000, 32, 0.0015);

    PWM->PWM_CH_NUM[0].PWM_CPRD = pwm_get_cprd(84000000, 32, 0.02);  //TODO
    PWM->PWM_CH_NUM[0].PWM_CDTY = pwm_get_cdty(84000000, 32, 0.0015);  //TODO: find period an duty cycle for motor_driver


    // PWM->PWM_IER1 = (1<<1);
    PWM->PWM_ENA = PWM_ENA_CHID1 | PWM_ENA_CHID0;  // PWM Enable Register, enable channel 1
    while(!(PWM->PWM_SR & (1<<1)));
    printf("pwm enabled\n\r");

}

void pwm_duty_cycle_update(double duty_cycle) {
    if(duty_cycle < 0.0009 || duty_cycle > 0.0021) {
        printf("Duty cycle ut of range \n\r");
    } else {
        uint32_t cdtyupd = pwm_get_cdty(84000000, 32, duty_cycle);
        PWM->PWM_CH_NUM[1].PWM_CDTYUPD = cdtyupd;
    }
    
    
}

void pwm_duty_cycle_update_speed(double duty_cycle) {
    //if(duty_cycle < 0.0009 || duty_cycle > 0.0021) {
        //printf("Duty cycle ut of range \n\r");
    //} else {
        uint32_t cdtyupd = pwm_get_cdty(84000000, 32, duty_cycle);
        PWM->PWM_CH_NUM[0].PWM_CDTYUPD = cdtyupd;
    //}
}



double pwm_percent_to_duty_cycle(char data) {
    if(data > 100) {data=100;}
    if(data < 0) {data=0;}
    double duty_cycle;
    duty_cycle = 0.0009 + (((double)data * (0.01 - 0.0009))/(100));
    return duty_cycle;
}

double pwm_percent_to_duty_cycle_speed(char data) {

}

