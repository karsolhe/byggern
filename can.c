#include "can.h"

void CAN_init(uint8_t mode) {
    mcp_init();
    mcp_set_mode(mode);
}

void CAN_send(uint8_t transmitBuffer, CAN_message_ptr message) {

	// Id. TXBnSIDH og TXBnSIDL
	mcp_write(MCP_TXB0SIDH, message->id / 8); // De åtte høyeste bitene i iden.
	mcp_write(MCP_TXB0SIDL, (message->id % 8) << 5); // De tre laveste bitene i iden.

	// Lengde. TXBnDLC
	mcp_write(MCP_TXB0DLC, message->length);

	// Melding. TXBnDm
	for (int i = 0; i < message->length; i++) {
		mcp_write(MCP_TXB0D0 + i, message->data[i]);
	}
    mcp_request_to_send(transmitBuffer);

}

CAN_message CAN_recieve() {
    // Alt her foregår med buffer 0
	message_t message = {};

	// Id. RXBnSIDH og RXBnSIDL
	uint8_t id_low = mcp_read(MCP_RXB0SIDL)/0b100000;
	uint8_t id_high = mcp_read(MCP_RXB0SIDH);
	message.id = id_high * 0b1000 + id_low;

	// Lengde. RXBnDLC
	message.length = mcp_read(MCP_RXB0DLC);

	// Melding. RXBnDM
	for (int i = 0; i < message.length; i++) {
		message.data[i] = mcp_read(MCP_RXB0D0 + i);
	}

	return message;
}
