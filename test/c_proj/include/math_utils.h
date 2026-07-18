#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <stdbool.h>

int add(int lhs, int rhs);
int subtract(int lhs, int rhs);
int clamp_int(int value, int minimum, int maximum);
bool is_even(int value);

#endif
