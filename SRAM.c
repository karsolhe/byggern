#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "SRAM.h"
#include <avr/io.h>

// Initialize SRAM
void SRAM_init(void) {
    MCUCR |= (1 << SRE); // Enable external memory
    SFIOR &= ~(0b111<<XMM0); // Clears the three last bits
    SFIOR |= (1 << XMM2); // Disables pins used by JTAG
}

// Convert num to binary (for debugging)
void print_binary(uint8_t num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

// Test SRAM for read and write operations
void SRAM_test(void) { 
    volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
    uint16_t ext_ram_size = 0x800;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    printf("Starting SRAM test...\n\r");
    // rand() stores some internal state, so calling this function in a loop will
    // yield different seeds each time (unless srand() is called before this function)
    uint16_t seed = rand();
    // Write phase: Immediately check that the correct value was stored
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = rand();
        ext_ram[i] = some_value;
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Write phase error: ext_ram[%4d] = ", i);
            print_binary(retreived_value);
            printf(" (should be ");
            print_binary(some_value);
            printf(" Mismatched bits ");
            print_binary(~(retreived_value ^ ~some_value));
            printf(")\n\r");
            write_errors++;
        }
    }
    // Retrieval phase: Check that no values were changed during or after the write phase
    srand(seed);
    // reset the PRNG to the state it had before the write phase
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = rand();
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Retrieval phase error: ext_ram[%4d] = ", i);
            print_binary(retreived_value);
            printf(" (should be ");
            print_binary(some_value);
            printf(")\n\r");
            retrieval_errors++;
        }
    }
    printf("SRAM test completed with \n\r%4d errors in write phase and \n\r%4d errors in retrieval phase\n\n\r", write_errors, retrieval_errors);
}
