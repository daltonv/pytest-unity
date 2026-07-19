#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_before_crash(void)
{
    TEST_ASSERT_EQUAL_INT(1, 1);
}

void test_causes_crash(void)
{
    int *p = NULL;
    TEST_ASSERT_EQUAL_INT(42, *p);
}

void test_after_crash(void)
{
    TEST_ASSERT_EQUAL_INT(2, 2);
}
