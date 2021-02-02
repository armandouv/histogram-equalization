//
// Created by armau on 01/02/2021.
//
#include <math.h>

long get_equalized_value(long value, long minimum, double factor)
{
    return (long) round( (double)(value - minimum) * factor) + 1;
}