#include "can.h"

void CAN_init() {
    mcp_init();
}

void CAN_send(CAN_message_ptr message) {
	mcp_write(MCP_TXB0SIDH, (message->ID >> 3)); //Eight highest bits of ID
	mcp_write(MCP_TXB0SIDL, (message->ID & 0b111) << 5); //Three lowest bit of ID
	mcp_write(MCP_TXB0DLC, message->length);

	for (int i = 0; i < message->length; i++) {
		mcp_write(MCP_TXB0D0 + i, message->data[i]);
	}

    mcp_request_to_send(0);
}

CAN_message CAN_recieve() {
    // RX0
	CAN_message message = {};

	uint8_t id_low = mcp_read(MCP_RXB0SIDL)/0x20;
	uint8_t id_high = mcp_read(MCP_RXB0SIDH);
	message.ID = id_high * 0x8 + id_low;

	message.length = mcp_read(MCP_RXB0DLC);

	for (int i = 0; i < message.length; i++) {
		message.data[i] = mcp_read(MCP_RXB0D0 + i);
	}

	return message;
}
