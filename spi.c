#include "spi.h"


void spi_slave_unselect() {
    PORTB |= (1 << DD_SS);
}

void spi_slave_select() {
    PORTB &= ~(1 << DD_SS);
}

// Initialize SPI
void spi_init() {
    // Set MOSI, SCK and slave select as output, all others input 
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
    // Enable SPI, set to Master, set clock rate fck/16  
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
    spi_slave_unselect();
}

// Transmit data with SPI
void spi_transmit(char data) {
    SPDR = data; // Putting data on SPDR starts transmission
    while(!(SPSR & (1<<SPIF)));  // Transmission complete when SPIF is set
}

// Recieve data with SPI
uint8_t spi_recieve() {
    // Send out dummy byte to initiate read
    SPDR = 0xFF; 
    while(!(SPSR & (1<<SPIF))); // Wait for dummy byte transmission
    return SPDR;
}

