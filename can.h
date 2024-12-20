#include "mcp2515.h"
#include <stdio.h>


typedef struct CAN_Message {
    uint8_t ID;  //can't use 11 bit ID as long as this is uint8_t
    uint8_t length;
    char data[8];
} CAN_message, *CAN_message_ptr;

void CAN_init();

void CAN_send(CAN_message_ptr message);

CAN_message CAN_recieve();