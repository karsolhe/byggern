#include <stdint.h>

#define EXT_MEM ((EXTERNAL_MEMORY*) 0x1000)

typedef struct {
    volatile uint32_t OLED_COMMAND[128];
    volatile uint32_t OLED_DATA[128];
    volatile uint32_t ADC[256];
    volatile uint32_t SRAM[512];
} EXTERNAL_MEMORY;

void address_decoder_test();
