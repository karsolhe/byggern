#include "buffer.h"



CircularBuffer msgBuffer;

void buffer_init(void) {
    msgBuffer.head = 0;
    msgBuffer.tail = 0;
}

bool buffer_add(const CanMsg *msg) {
    uint32_t next = (msgBuffer.head + 1) % 5;
    
    if (next == msgBuffer.tail) {
        return false;  // Buffer full
    }
    
    msgBuffer.buffer[msgBuffer.head] = *msg;
    msgBuffer.head = next;
    
    return true;
}

bool buffer_get(CanMsg *msg) {
    if (msgBuffer.head == msgBuffer.tail) {
        return false;  // Buffer empty
    }
    
    *msg = msgBuffer.buffer[msgBuffer.tail];
    msgBuffer.tail = (msgBuffer.tail + 1) % 5;
    
    return true;
}

bool buffer_is_empty(void) {
    return msgBuffer.head == msgBuffer.tail;
}