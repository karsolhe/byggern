#include "mcp2515.h"
#include <util/delay.h>


void mcp_init( ) {
    spi_init();
    mcp_reset();
    _delay_ms(1);
}

void mcp_timing() {
    mcp_set_mode(MODE_CONFIG);
    mcp_write(MCP_CNF1, 0b11000011); //Synchronization Jump Width Length 11 and baud rate prescaler = 3
    mcp_write(MCP_CNF2, 0b10011011); // set phase 3 in CNF3, sample once, PS1 length, propagation segment length
    mcp_write(MCP_CNF3, 0b00000011); //last three bits set PS2 length
}


uint8_t mcp_read(uint8_t address) {
    spi_slave_select();
    spi_transmit(MCP_READ);  //sier til mcp at vi skal utføre read
    spi_transmit(address);   //sender adressen til MCP
    uint8_t data = spi_recieve();   //leser fra MCP, som nå vil ha lagt riktig data på SDPR
    spi_slave_unselect();
    return data;
}

void mcp_write(uint8_t address, uint8_t data) {
    spi_slave_select();
    spi_transmit(MCP_WRITE);
    spi_transmit(address);
    spi_transmit(data);
    spi_slave_unselect();
}


void mcp_request_to_send(uint8_t transmitBuffer) {
    spi_slave_select();
    uint8_t data = 0;
    switch(transmitBuffer) {
        case 0:
            data = MCP_RTS_TX0;
            break;
        case 1:
            data = MCP_RTS_TX1;
            break;
        case 2:
            data = MCP_RTS_TX2;
            break;
        case 3:
            data = MCP_RTS_ALL;
            break;
    }
    spi_transmit(data);
    spi_slave_unselect();
}

uint8_t mcp_read_status() {
    spi_slave_select();
    spi_transmit(MCP_READ_STATUS);
    uint8_t data = spi_recieve();
    spi_slave_unselect();
    return data;
}

void mcp_bit_modify(uint8_t address, uint8_t data, uint8_t mask) {
    spi_slave_select();
    spi_transmit(MCP_BITMOD);
    spi_transmit(address);
    spi_transmit(mask);
    spi_transmit(data);
    spi_slave_unselect();
}

void mcp_reset() {
    spi_slave_select();
    spi_transmit(MCP_RESET);
    spi_slave_unselect();
}

void mcp_set_mode(uint8_t mode) {
    uint8_t bits_to_set = 0x00;
    switch (mode)
    {
    case 0x00: //NORMAL
        bits_to_set = 0b00000000;
        break;
    case 0x20: //SLEEP
        bits_to_set = 0b00100000;
        break;
    case 0x40: //LOOPBACK
        bits_to_set = 0b01000000;
        break;
    case 0x60: //LISTENONLY
        bits_to_set = 0b01100000;
        break;
    case 0x80:
        bits_to_set = 0b10000000;
        break;
    default:
        break;
    }
    mcp_bit_modify(MCP_CANCTRL,  bits_to_set, MODE_MASK);
}

uint8_t mcp_check_mode() {
    uint8_t canstat = mcp_read(MCP_CANSTAT);
    return (canstat & MODE_MASK);
}