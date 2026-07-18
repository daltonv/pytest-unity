#include "unity.h"

#include "math_utils.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_add_returns_sum_of_two_positive_numbers(void)
{
    TEST_ASSERT_EQUAL_INT(7, add(3, 4));
}

void test_add_handles_negative_numbers(void)
{
    TEST_ASSERT_EQUAL_INT(-5, add(-2, -3));
}

void test_subtract_returns_difference(void)
{
    TEST_ASSERT_EQUAL_INT(6, subtract(10, 4));
}

void test_is_even_identifies_even_and_odd_numbers(void)
{
    TEST_ASSERT_TRUE(is_even(8));
    TEST_ASSERT_FALSE(is_even(7));
}
