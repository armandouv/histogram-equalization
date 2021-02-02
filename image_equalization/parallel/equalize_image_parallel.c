//
// Created by armau on 01/02/2021.
//
#include <omp.h>
#include <stdio.h>
#include "cumulative_distribution_parallel.h"
#include "generate_image_parallel.h"
#include "histogram_parallel.h"
#include "../sequential/cumulative_distribution_sequential.h"
#include "../../util/get_first_nonzero.h"
#include "../../util/generate_csv.h"
#include "../../util/filenames.h"
#include "../../util/generate_array.h"
#include "../../util/constants.h"
#include "../../util/get_equalized_value.h"
#include "../../stb-master/stb_image_write.h"

double equalize_image_parallel(unsigned char *image, int width, int height, int number_of_channels, char *image_name)
{
    long size = width * height;
    long *histogram = generate_empty_long_array(MAX_COLOR_VALUE);
    long *new_histogram = generate_empty_long_array(MAX_COLOR_VALUE);
    long *cumulative_distribution = generate_empty_long_array(MAX_COLOR_VALUE);
    unsigned char *new_image = generate_empty_unsigned_char_array(size * number_of_channels);

    double start, end;
    int number_of_processors = omp_get_num_procs();
    omp_set_num_threads(number_of_processors);

    start = omp_get_wtime();
    generate_histogram_parallel(histogram, image, size, number_of_channels);
    get_cumulative_distribution_sequential(cumulative_distribution, histogram);
    long cumulative_distribution_minimum = get_first_nonzero(cumulative_distribution);
    get_equalized_cumulative_distribution_parallel(cumulative_distribution, cumulative_distribution_minimum, size);
    generate_image_parallel(image, new_image, number_of_channels, cumulative_distribution, size);
    generate_histogram_parallel(new_histogram, new_image, size, number_of_channels);
    end = omp_get_wtime();
    /*long cumulative_distribution_minimum;
    double numerator = (double) MAX_COLOR_VALUE - 2;
    double denominator;
    double FACTOR;
    start = omp_get_wtime();
    #pragma omp parallel
    {
        // Generate histogram
        #pragma omp for reduction(+:histogram[:MAX_COLOR_VALUE])
        for (int i = 0; i < size * number_of_channels; i += number_of_channels)
        {
            histogram[image[i]]++;
        }
        // Get cumulative distribution and minimum.
        #pragma omp single
        {
            get_cumulative_distribution_sequential(cumulative_distribution, histogram);
            cumulative_distribution_minimum = get_first_nonzero(cumulative_distribution);
            denominator = (double) size - cumulative_distribution_minimum;
            FACTOR = numerator / denominator;
        }
        // Get equalized cumulative distribution.
        #pragma omp for
        for (int i = 0; i < MAX_COLOR_VALUE; ++i)
        {
            cumulative_distribution[i] = get_equalized_value(cumulative_distribution[i], cumulative_distribution_minimum, FACTOR);
        }
        // Generate new image.
        #pragma omp for
        for (int i = 0; i < size * number_of_channels; i++)
        {
            unsigned char original_value = image[i];
            if (i % number_of_channels == 0) new_image[i] = (unsigned char) cumulative_distribution[original_value];
            else new_image[i] = (unsigned char) original_value;
        }
        // Generate new image histogram.
        #pragma omp for reduction(+:new_histogram[:MAX_COLOR_VALUE])
        for (int i = 0; i < size * number_of_channels; i += number_of_channels)
        {
            new_histogram[new_image[i]]++;
        }
    }
    end = omp_get_wtime();*/

    generate_csv(histogram, new_histogram, image_name, "_parallel");

    char *new_sequential_name = generate_new_filename(image_name, "_eq_parallel.jpg");
    stbi_write_jpg(new_sequential_name, width, height, number_of_channels, new_image, QUALITY);

    free(histogram);
    free(new_histogram);
    free(cumulative_distribution);
    free(new_image);

    return end - start;
}






