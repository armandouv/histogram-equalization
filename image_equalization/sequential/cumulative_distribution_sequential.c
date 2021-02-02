//
// Created by armau on 01/02/2021.
//

#include "../../util/constants.h"
#include "../../util/get_equalized_value.h"


void get_cumulative_distribution_sequential(long *histogram)
{
    for (int i = 1; i < MAX_COLOR_VALUE; ++i)
    {
        histogram[i] += histogram[i - 1];
    }
}

void get_equalized_cumulative_distribution_sequential(long *cumulative_distribution, long minimum, long size)
{
    double numerator = (double) MAX_COLOR_VALUE - 2;
    double denominator = (double) size - minimum;
    double FACTOR = numerator / denominator;

    for (int i = 0; i < MAX_COLOR_VALUE; ++i)
    {
        cumulative_distribution[i] = get_equalized_value(cumulative_distribution[i], minimum, FACTOR);
    }
}