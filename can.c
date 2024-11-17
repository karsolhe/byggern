#include "can.h"

// Initialize CAN
void CAN_init() {
    mcp_init();
}

// Send message with CAN
void CAN_send(CAN_message_ptr message) {
	mcp_write(MCP_TXB0SIDH, (message->ID >> 3)); // Eight highest bits of ID
	mcp_write(MCP_TXB0SIDL, (message->ID & 0b111) << 5); // Three lowest bit of ID
	mcp_write(MCP_TXB0DLC, message->length);

	// Iterate over bytes in buffer and place data to be transmitted here
	for (int i = 0; i < message->length; i++) {
		mcp_write(MCP_TXB0D0 + i, message->data[i]);
	}

	// Transmit to MCP_RTS_TX0
    mcp_request_to_send(0);
}

// Recieve CAN message
CAN_message CAN_recieve() {
    // Buffer RX0
	CAN_message message = {};

	// Read buffers to recieve message
	uint8_t id_low = (mcp_read(MCP_RXB0SIDL) / 0x20); // Right shift first bits in buffer to get low bits of ID
	uint8_t id_high = mcp_read(MCP_RXB0SIDH); // Read buffer for high bits of ID
	message.ID = (id_high * 0x8 ) + id_low; // Left shift high ID bits and add low ID bits to get the correct message ID

	// Read message length from register
	message.length = mcp_read(MCP_RXB0DLC);

	// Iterate over bytes in recieve buffer to recieve the data
	for (int i = 0; i < message.length; i++) {
		message.data[i] = mcp_read(MCP_RXB0D0 + i);
	}

	return message;
}
