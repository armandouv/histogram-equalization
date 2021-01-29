//
// Created by armau on 28/01/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION

#include "stb-master/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb-master/stb_image_write.h"

#define MAX_COLOR_VALUE 256

unsigned char *generate_histogram(unsigned char *image, long length, int number_of_channels);

unsigned char *generate_empty_unsigned_char_array(long length);

long *generate_empty_long_array(long length);

long *get_cumulative_distribution(unsigned char *histogram);

long get_minimum(long *cumulative_distribution);

long get_equalized_value(long value, long minimum, double factor);

long *get_equalized_cumulative_distribution(long *cumulative_distribution, long minimum, int width, int height);


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: main (Ubicacion de la imagen)\n");
        return -1;
    }

    char *image_path = argv[1];
    int width, height, number_of_channels;
    unsigned char *image = stbi_load(image_path, &width, &height, &number_of_channels, 0);

    if (image == NULL)
    {
        printf("No se pudo abrir la imagen.\n");
        return -1;
    }

    printf("Ubicacion de la imagen: %s\n", image_path);
    printf("Ancho: %d\n", width);
    printf("Alto: %d\n", height);
    printf("Numero de canales: %d\n", number_of_channels);

    unsigned char *histogram = generate_histogram(image, width * height, number_of_channels);
    long *cumulative_distribution = get_cumulative_distribution(histogram);
    long cumulative_distribution_minimum = get_minimum(cumulative_distribution);
    long *equalized_cumulative_distribution = get_equalized_cumulative_distribution(histogram);


    //free used
    return 0;
}

unsigned char *generate_empty_unsigned_char_array(long length)
{
    unsigned char *empty = malloc(sizeof(unsigned char) * length);

    for (int i = 0; i < length; ++i)
    {
        empty[i] = 0;
    }

    return empty;
}

long *generate_empty_long_array(long length)
{
    long *empty = malloc(sizeof(long) * length);

    for (int i = 0; i < length; ++i)
    {
        empty[i] = 0;
    }

    return empty;
}


unsigned char *generate_histogram(unsigned char *image, long length, int number_of_channels)
{
    unsigned char *histogram = generate_empty_unsigned_char_array(MAX_COLOR_VALUE);

    for (int i = 0; i < MAX_COLOR_VALUE; ++i)
    {
        histogram[i] = 0;
    }

    for (int i = number_of_channels - 1; i < length; ++i)
    {
        histogram[image[i]]++;
    }

    return histogram;
}

long *get_cumulative_distribution(unsigned char *histogram)
{
    long *cumulative_distribution = generate_empty_long_array(MAX_COLOR_VALUE);

    cumulative_distribution[0] = histogram[0];
    for (int i = 1; i < MAX_COLOR_VALUE; ++i)
    {
        cumulative_distribution[i] = histogram[i] + cumulative_distribution[i - 1];
    }

    return cumulative_distribution;
}

long get_minimum(long *cumulative_distribution)
{
    for (int i = 0; i < MAX_COLOR_VALUE; ++i)
    {
        if (cumulative_distribution[i] != 0) return cumulative_distribution[i];
    }

    return -1;
}

long get_equalized_value(long value, long minimum, double factor)
{
    return round((value - minimum) * factor) + 1;
}

long *get_equalized_cumulative_distribution(long *cumulative_distribution, long minimum, int width, int height)
{
    long *equalized_cumulative_distribution = generate_empty_long_array(MAX_COLOR_VALUE);

    double FACTOR = (MAX_COLOR_VALUE - 2) / ((width * height) - minimum);


    for (int i = 0; i < MAX_COLOR_VALUE; ++i)
    {
        equalized_cumulative_distribution[i] = get_equalized_value(cumulative_distribution[i], minimum, FACTOR);
    }

    return equalized_cumulative_distribution;
}

