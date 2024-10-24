#include "spi.h"


void spi_slave_unselect() {
    PORTB |= (1 << DD_SS);
}

void spi_slave_select() {
    PORTB &= ~(1 << DD_SS);
}

void spi_master_init() {
    // Set MOSI and SCK output, all others input 
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
    // Enable SPI, Master, set clock rate fck/16  
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
    spi_slave_unselect();
}


void spi_transmit(char cData) {
    // Start transmission 
    SPDR = cData;
    // Wait for transmission complete 
    while(!(SPSR & (1<<SPIF)));
}

uint8_t spi_recieve() {
    //send out dummy byte to initiate read
    SPDR = 0xFF;
    // Wait for reception complete 
    while(!(SPSR & (1<<SPIF)));
    // Return data register 
    return SPDR;
}

