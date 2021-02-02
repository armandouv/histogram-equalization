//
// Created by armau on 01/02/2021.
//

#include "../../util/constants.h"
#include "../../util/get_equalized_value.h"

void get_equalized_cumulative_distribution_parallel(long *cumulative_distribution, long minimum, long size)
{
    double numerator = (double) MAX_COLOR_VALUE - 2;
    double denominator = (double) size - minimum;
    double FACTOR = numerator / denominator;

    #pragma omp parallel for
    for (int i = 0; i < MAX_COLOR_VALUE; ++i)
    {
        cumulative_distribution[i] = get_equalized_value(cumulative_distribution[i], minimum, FACTOR);
    }
}