//
// Created by armau on 01/02/2021.
//
#include "../../util/constants.h"
#include <stdio.h>

void generate_histogram_parallel(long *histogram, unsigned char *image, long size, int number_of_channels)
{
    #pragma omp parallel for reduction(+:histogram[:MAX_COLOR_VALUE])
    for (int i = 0; i < size * number_of_channels; i += number_of_channels)
    {
        histogram[image[i]]++;
    }
}