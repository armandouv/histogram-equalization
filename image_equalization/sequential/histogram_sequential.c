//
// Created by armau on 01/02/2021.
//
#include "../../util/constants.h"

void generate_histogram_sequential(long *histogram, unsigned char *image, long size, int number_of_channels)
{
    for (int i = 0; i < size * number_of_channels; i += number_of_channels)
    {
        histogram[image[i]]++;
    }
}