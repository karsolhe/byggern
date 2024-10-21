#include "mcp2515.h"

typedef struct CAN_Message {
    int ID;
    uint8_t length;
    char data[8];
} CAN_message, *CAN_message_ptr;

void CAN_init(uint8_t mode);

void CAN_send(uint8_t transmitBuffer, uint8_t address, uint8_t data);

CAN_message CAN_recieve();