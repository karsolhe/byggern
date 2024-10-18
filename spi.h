#include <stdint.h>
#include <avr/io.h>
#define DDR_SPI DDRB
#define DD_MOSI DDB5
#define DD_MISO DDB6
#define DD_SCK DDB7
#define DD_SS DDB4


void spi_master_init();

void spi_slave_unselect();

void spi_slave_select();

void spi_transmit(char cData);

uint8_t spi_recieve();

