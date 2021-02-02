//
// Created by armau on 01/02/2021.
//
#include "constants.h"

long get_first_nonzero(long *histogram)
{
    for (int i = 0; i < MAX_COLOR_VALUE; ++i)
    {
        if (histogram[i] != 0) return histogram[i];
    }

    return -1;
}