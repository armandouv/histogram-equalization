//
// Created by armau on 01/02/2021.
//
#include <omp.h>
#include "cumulative_distribution_sequential.h"
#include "generate_image_sequential.h"
#include "histogram_sequential.h"
#include "../../util/get_first_nonzero.h"
#include "../../util/generate_csv.h"
#include "../../util/filenames.h"
#include "../../util/generate_array.h"
#include "../../util/constants.h"
#include "../../stb-master/stb_image_write.h"
#include <stdio.h>

double equalize_image_sequential(unsigned char *image, int width, int height, int number_of_channels, char *image_name)
{
    long size = width * height;
    long *histogram = generate_empty_long_array(MAX_COLOR_VALUE);
    long *new_histogram = generate_empty_long_array(MAX_COLOR_VALUE);
    long *cumulative_distribution = generate_empty_long_array(MAX_COLOR_VALUE);
    unsigned char *new_image = generate_empty_unsigned_char_array(size * number_of_channels);

    double start = omp_get_wtime();

    generate_histogram_sequential(histogram, image, size, number_of_channels);
    get_cumulative_distribution_sequential(cumulative_distribution, histogram);
    long cumulative_distribution_minimum = get_first_nonzero(cumulative_distribution);
    get_equalized_cumulative_distribution_sequential(cumulative_distribution, cumulative_distribution_minimum, size);
    generate_image_sequential(image, new_image, number_of_channels, cumulative_distribution, size);
    generate_histogram_sequential(new_histogram, new_image, size, number_of_channels);

    double end = omp_get_wtime();

    double start_csv = omp_get_wtime();
    generate_csv(histogram, new_histogram, image_name, "_sequential");
    double end_csv = omp_get_wtime();

    char *new_sequential_name = generate_new_filename(image_name, "_eq_sequential.jpg");

    double start_image_generation = omp_get_wtime();
    stbi_write_jpg(new_sequential_name, width, height, number_of_channels, new_image, QUALITY);
    double end_image_generation = omp_get_wtime();

    printf("\nTiempo de generacion de csv (secuencial): %f\n", end_csv - start_csv);
    printf("Tiempo de generacion de imagen (secuencial): %f\n", end_image_generation - start_image_generation);

    free(histogram);
    free(new_histogram);
    free(cumulative_distribution);
    free(new_image);

    return end - start;
}






