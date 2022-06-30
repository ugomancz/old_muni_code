//
// Created by xkostik on 19-Nov-20. Greatly inspired by https://embeddedartistry.com/
//

#ifndef UNTITLED_CIR_BUFFER_H
#define UNTITLED_CIR_BUFFER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct cir_buffer {
    uint8_t *data;
    size_t head;
    size_t tail;
    size_t max_size;
    bool full;
};

typedef struct cir_buffer *cir_buffer_handle;

/**
 * @param buffer is pointer to data storage
 * @param size is size of data storage
 * @return handle of cir_buffer struct
 */
cir_buffer_handle cir_buffer_init(uint8_t *buffer, size_t size);

/**
 * @brief puts data into buffer
 * @param buffer_handle
 * @param data
 * @return 0 on success, else -1
 */
int cir_buffer_put(cir_buffer_handle buffer_handle, uint8_t data);

/**
 * @brief reads data from buffer
 * @param buffer_handle
 * @param pointer to data destination
 * @return 0 on success, else -1
 */
int cir_buf_get(cir_buffer_handle buffer_handle, uint8_t *data);

/**
 * @param buffer_handle
 * @return true if buffer is empty
 */
bool cir_buf_empty(cir_buffer_handle buffer_handle);

#endif //UNTITLED_CIR_BUFFER_H
