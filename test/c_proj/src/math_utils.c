#include "math_utils.h"

int add(int lhs, int rhs)
{
    return lhs + rhs;
}

int subtract(int lhs, int rhs)
{
    return lhs - rhs;
}

int clamp_int(int value, int minimum, int maximum)
{
    if (value < minimum) {
        return minimum;
    }

    if (value > maximum) {
        return maximum;
    }

    return value;
}

bool is_even(int value)
{
    return (value % 2) == 0;
}
