//
// Created by armau on 01/02/2021.
//
#include "../../util/constants.h"
#include <stdio.h>

void generate_histogram_parallel(long *histogram, unsigned char *image, long size, int number_of_channels)
{
    long hist[256] = {0};
    #pragma omp parallel for reduction(+:hist[:])
    for (int i = 0; i < size * number_of_channels; i += number_of_channels)
    {
        hist[image[i]]++;
    }

    for (int i = 0; i < 256; ++i)
    {
        histogram[i] = hist[i];
    }
}