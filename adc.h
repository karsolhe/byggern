#include <stdint.h>

// typedef struct pos_t{
//     int x;
//     int y;
// };

void adc_init();

uint8_t adc_read(uint8_t channel); //volatile

void pos_calibrate();

// pos_t pos_read(void);
