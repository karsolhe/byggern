#include "can.h"
#include <stdio.h>
#include <stdbool.h>


typedef struct {
    CanMsg buffer[5];
    volatile uint32_t head;  // Write index
    volatile uint32_t tail;  // Read index
} CircularBuffer;

extern CircularBuffer msgBuffer;

void buffer_init(void);
// Add message to buffer - called from handler
bool buffer_add(const CanMsg *msg);
// Get message from buffer - called from main context
bool buffer_get(CanMsg *msg);
bool buffer_is_empty(void);


