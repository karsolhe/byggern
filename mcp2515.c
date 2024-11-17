#include "mcp2515.h"
#include <util/delay.h>

// Initialize MCP2515
void mcp_init( ) {
    spi_init();
    mcp_reset();
    _delay_ms(1);
}

// Changes the CNF registers in the right order
void mcp_timing() {
    mcp_set_mode(MODE_CONFIG);
    mcp_write(MCP_CNF1, 0b11000011); // Synchronization Jump Width Length 11 and baud rate prescaler = 3
    mcp_write(MCP_CNF2, 0b10011011); // Set phase 3 in CNF3, sample once, PS1 length, propagation segment length
    mcp_write(MCP_CNF3, 0b00000011); // Last three bits set PS2 length
}

// Read data from address from MCP2515
uint8_t mcp_read(uint8_t address) {
    spi_slave_select();
    spi_transmit(MCP_READ);  // Tells MCP to perform a read
    spi_transmit(address);   // Sends address to MCP
    uint8_t data = spi_recieve();   // Read MCP that has now put the correct data on SDPR
    spi_slave_unselect();
    return data;
}

// Write data to address on MCP2515
void mcp_write(uint8_t address, uint8_t data) {
    spi_slave_select();
    spi_transmit(MCP_WRITE); // Tells MCP to perform a write
    spi_transmit(address); // Sends address to MCP
    spi_transmit(data); // Transmit data
    spi_slave_unselect();
}

// Transmit to chosen RTS register that transmits the data
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

// Returns status on MCP2515
uint8_t mcp_read_status() {
    spi_slave_select();
    spi_transmit(MCP_READ_STATUS);
    uint8_t data = spi_recieve();
    spi_slave_unselect();
    return data;
}

// Mask chosen bits for selected address 
void mcp_bit_modify(uint8_t address, uint8_t data, uint8_t mask) {
    spi_slave_select();
    spi_transmit(MCP_BITMOD);
    spi_transmit(address);
    spi_transmit(mask);
    spi_transmit(data);
    spi_slave_unselect();
}

// Resets the registers on MCP2515
void mcp_reset() {
    spi_slave_select();
    spi_transmit(MCP_RESET);
    spi_slave_unselect();
}

// Selects mode for MCP2515
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
    case 0x80: //CONFIG
        bits_to_set = 0b10000000;
        break;
    default:
        break;
    }
    mcp_bit_modify(MCP_CANCTRL,  bits_to_set, MODE_MASK);
}

// Returns mode on MCP2515
uint8_t mcp_check_mode() {
    uint8_t canstat = mcp_read(MCP_CANSTAT);
    return (canstat & MODE_MASK);
}