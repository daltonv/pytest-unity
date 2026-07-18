#include "unity.h"

#include "ring_buffer.h"

static ring_buffer_t buffer;

void setUp(void)
{
    ring_buffer_init(&buffer);
}

void tearDown(void)
{
}

void test_new_buffer_is_empty(void)
{
    TEST_ASSERT_TRUE(ring_buffer_is_empty(&buffer));
    TEST_ASSERT_FALSE(ring_buffer_is_full(&buffer));
    TEST_ASSERT_EQUAL_size_t(0U, ring_buffer_size(&buffer));
}

void test_push_and_pop_preserve_fifo_order(void)
{
    uint8_t value = 0U;

    TEST_ASSERT_TRUE(ring_buffer_push(&buffer, 10U));
    TEST_ASSERT_TRUE(ring_buffer_push(&buffer, 20U));

    TEST_ASSERT_TRUE(ring_buffer_pop(&buffer, &value));
    TEST_ASSERT_EQUAL_UINT8(10U, value);

    TEST_ASSERT_TRUE(ring_buffer_pop(&buffer, &value));
    TEST_ASSERT_EQUAL_UINT8(20U, value);
}

void test_push_fails_when_buffer_is_full(void)
{
    TEST_ASSERT_TRUE(ring_buffer_push(&buffer, 1U));
    TEST_ASSERT_TRUE(ring_buffer_push(&buffer, 2U));
    TEST_ASSERT_TRUE(ring_buffer_push(&buffer, 3U));
    TEST_ASSERT_TRUE(ring_buffer_push(&buffer, 4U));

    TEST_ASSERT_TRUE(ring_buffer_is_full(&buffer));
    TEST_ASSERT_FALSE(ring_buffer_push(&buffer, 5U));
}

void test_pop_fails_when_buffer_is_empty(void)
{
    uint8_t value = 0U;

    TEST_ASSERT_FALSE(ring_buffer_pop(&buffer, &value));
}

void test_buffer_wraps_around_after_pop(void)
{
    uint8_t value = 0U;

    TEST_ASSERT_TRUE(ring_buffer_push(&buffer, 1U));
    TEST_ASSERT_TRUE(ring_buffer_push(&buffer, 2U));
    TEST_ASSERT_TRUE(ring_buffer_push(&buffer, 3U));

    TEST_ASSERT_TRUE(ring_buffer_pop(&buffer, &value));
    TEST_ASSERT_EQUAL_UINT8(1U, value);

    TEST_ASSERT_TRUE(ring_buffer_push(&buffer, 4U));
    TEST_ASSERT_TRUE(ring_buffer_push(&buffer, 5U));

    TEST_ASSERT_TRUE(ring_buffer_pop(&buffer, &value));
    TEST_ASSERT_EQUAL_UINT8(2U, value);
    TEST_ASSERT_TRUE(ring_buffer_pop(&buffer, &value));
    TEST_ASSERT_EQUAL_UINT8(3U, value);
    TEST_ASSERT_TRUE(ring_buffer_pop(&buffer, &value));
    TEST_ASSERT_EQUAL_UINT8(4U, value);
    TEST_ASSERT_TRUE(ring_buffer_pop(&buffer, &value));
    TEST_ASSERT_EQUAL_UINT8(5U, value);
}
