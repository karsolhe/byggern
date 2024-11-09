#include "ir.h"


uint8_t ir_read() {
    uint16_t adc = adc_ir_read();
    if(adc < 2000) {
        return 1;
    } else {return 0;}
};

void ir_point_counter(int *hp) {
    if(ir_read() == 1) {
        (*hp)--;
        time_spinFor(msecs(80));
    }
};

