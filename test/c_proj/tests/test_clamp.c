#include "unity.h"

#include "math_utils.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_clamp_returns_minimum_when_value_is_too_low(void)
{
    TEST_ASSERT_EQUAL_INT(0, clamp_int(-10, 0, 100));
}

void test_clamp_returns_maximum_when_value_is_too_high(void)
{
    TEST_ASSERT_EQUAL_INT(100, clamp_int(150, 0, 100));
}

void test_clamp_returns_value_when_it_is_in_range(void)
{
    TEST_ASSERT_EQUAL_INT(42, clamp_int(42, 0, 100));
}

void test_clamp_accepts_values_equal_to_bounds(void)
{
    TEST_ASSERT_EQUAL_INT(0, clamp_int(0, 0, 100));
    TEST_ASSERT_EQUAL_INT(100, clamp_int(100, 0, 100));
}
