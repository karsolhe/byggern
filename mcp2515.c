#include "mcp2515.h"



void mcp_init() {
    spi_master_init();
    mcp_reset();
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
    spi_slave_unselect():
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
    spi_transmit();
    spi_slave_unselect():
}

void mcp_set_mode(uint8_t mode) {
    uint8_t bits_to_set;
    switch (mode)
    {
    case MODE_NORMAL:
        bits_to_set = 0b00000000;
        break;
    case MODE_SLEEP:
        bits_to_set = 0b00100000;
        break;
    case MODE_LOOPBACK:
        bits_to_set = 0b01000000;
        break;
    case MODE_LISTENONLY:
        bits_to_set = 0b01100000;
        break;
    case MODE_CONFIG:
        bits_to_set = 0b10000000;
        break;
    default:
        break;
    }
    mcp_bit_modify(MCP_CANCTRL, MODE_MASK, bits_to_set);
}

uint8_t mcp_check_mode() {
    uint8_t canstat = mcp_read(MCP_CANSTAT);
    return (canstat & MODE_MASK)
}