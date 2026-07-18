#include "ring_buffer.h"

void ring_buffer_init(ring_buffer_t *buffer)
{
    buffer->head = 0U;
    buffer->tail = 0U;
    buffer->count = 0U;
}

bool ring_buffer_push(ring_buffer_t *buffer, uint8_t value)
{
    if (ring_buffer_is_full(buffer)) {
        return false;
    }

    buffer->data[buffer->head] = value;
    buffer->head = (buffer->head + 1U) % RING_BUFFER_CAPACITY;
    buffer->count++;

    return true;
}

bool ring_buffer_pop(ring_buffer_t *buffer, uint8_t *value)
{
    if (ring_buffer_is_empty(buffer)) {
        return false;
    }

    *value = buffer->data[buffer->tail];
    buffer->tail = (buffer->tail + 1U) % RING_BUFFER_CAPACITY;
    buffer->count--;

    return true;
}

bool ring_buffer_is_empty(const ring_buffer_t *buffer)
{
    return buffer->count == 0U;
}

bool ring_buffer_is_full(const ring_buffer_t *buffer)
{
    return buffer->count == RING_BUFFER_CAPACITY;
}

size_t ring_buffer_size(const ring_buffer_t *buffer)
{
    return buffer->count;
}
