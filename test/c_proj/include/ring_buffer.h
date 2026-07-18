#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define RING_BUFFER_CAPACITY 4U

typedef struct {
    uint8_t data[RING_BUFFER_CAPACITY];
    size_t head;
    size_t tail;
    size_t count;
} ring_buffer_t;

void ring_buffer_init(ring_buffer_t *buffer);
bool ring_buffer_push(ring_buffer_t *buffer, uint8_t value);
bool ring_buffer_pop(ring_buffer_t *buffer, uint8_t *value);
bool ring_buffer_is_empty(const ring_buffer_t *buffer);
bool ring_buffer_is_full(const ring_buffer_t *buffer);
size_t ring_buffer_size(const ring_buffer_t *buffer);

#endif
