#include <stdlib.h>
#include "cir_buffer.h"

cir_buffer_handle cir_buffer_init(uint8_t *buffer, size_t size) {
    cir_buffer_handle buff = calloc(1, sizeof(struct cir_buffer));

    buff->data = buffer;
    buff->head = 0;
    buff->tail = 0;
    buff->max_size = size;
    buff->full = false;

    return buff;
}

void advance_pointer(cir_buffer_handle buffer_handle) {
    if (buffer_handle->full) {
        buffer_handle->tail = (buffer_handle->tail + 1) % buffer_handle->max_size;
    }
    buffer_handle->head = (buffer_handle->head + 1) % buffer_handle->max_size;
    buffer_handle->full = (buffer_handle->head == buffer_handle->tail);
}

int cir_buffer_put(cir_buffer_handle buffer_handle, uint8_t data) {
    if (!buffer_handle->full) {
        buffer_handle->data[buffer_handle->head] = data;
        advance_pointer(buffer_handle);
        return 0;
    }
    return -1;
}

bool cir_buf_empty(cir_buffer_handle buffer_handle) {
    return (buffer_handle->head == buffer_handle->tail) && !buffer_handle->full;
}

int cir_buf_get(cir_buffer_handle buffer_handle, uint8_t *data) {
    if (!cir_buf_empty(buffer_handle)) {
        *data = buffer_handle->data[buffer_handle->tail];
        buffer_handle->tail = (buffer_handle->tail + 1) % buffer_handle->max_size;
        buffer_handle->full = false;
        return 0;
    }
    return -1;
}


