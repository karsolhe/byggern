#include "ir.h"

// Returns 1 if IR diode is blocked, 0 if not
uint8_t ir_read() {
    uint16_t adc = adc_ir_read();
    if(adc < 2000) {
        return 1;
    } else {return 0;}
};

// If IR diode is blocked a life is lost and the function returns 1, else it returns 0
int ir_point_counter(int *hp) {
    if(ir_read() == 1) {
        (*hp)--;
        time_spinFor(msecs(80));
        return 1;
    }
    return 0;
};

