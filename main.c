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

#define QUALITY 100


char *get_image_name(char *image_path);

char *generate_new_name(char *original, char *suffix);

long *generate_histogram(unsigned char *image, long size, int number_of_channels);

unsigned char *generate_empty_unsigned_char_array(long size);

long *generate_empty_long_array(long length);

long *get_cumulative_distribution(long *histogram);

long get_minimum(long *cumulative_distribution);

long get_equalized_value(long value, long minimum, double factor);

long *get_equalized_cumulative_distribution(long *cumulative_distribution, long minimum, long size);

unsigned char *generate_image(unsigned char *original_image, int number_of_channels, long *equalized_cumulative_distribution, long size);

void generate_csv(long *original_histogram, long *equalized_histogram, char* suffix);

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

    long size = width * height;
    long *histogram = generate_histogram(image, size, number_of_channels);
    long *cumulative_distribution = get_cumulative_distribution(histogram);
    long cumulative_distribution_minimum = get_minimum(cumulative_distribution);
    long *equalized_cumulative_distribution = get_equalized_cumulative_distribution(cumulative_distribution, cumulative_distribution_minimum, size);
    unsigned char *new_image = generate_image(image, number_of_channels, equalized_cumulative_distribution, size);
    long *new_histogram = generate_histogram(new_image, size, number_of_channels);

    char *original_name = get_image_name(image_path);
    char *new_name = generate_new_name(original_name, "_eq_sequential.jpg");
    stbi_write_jpg(new_name, width, height, number_of_channels, new_image, QUALITY);
    generate_csv(histogram, new_histogram, "sequential");

    stbi_image_free(image);
    stbi_image_free(new_image);
    free(histogram);
    free(new_histogram);
    free(cumulative_distribution);
    free(equalized_cumulative_distribution);
    free(original_name);
    free(new_name);
    return 0;
}

void generate_csv(long *original_histogram, long *equalized_histogram, char* suffix)
{
    char *filename = generate_new_name("out/histogram_", suffix);
    filename = generate_new_name(filename, ".csv");
    FILE *csv = fopen(filename, "w+");

    for (int i = 0; i < MAX_COLOR_VALUE; i++)
        fprintf(csv, "%d,%ld,%ld\n", i, original_histogram[i], equalized_histogram[i]);

    fclose(csv);
}

char *get_image_name(char *image_path)
{
    char *image_name = strrchr(image_path, '/');
    if (image_name == NULL) image_name = image_path;
    else image_name++;
    return strtok(image_name, ".");
}

char *generate_new_name(char *original, char *suffix)
{
    char *new_image_name = malloc(sizeof(char) * 1000);
    snprintf(new_image_name, sizeof(char) * 1000, "%s%s", original, suffix);
    return new_image_name;
}

unsigned char *generate_empty_unsigned_char_array(long size)
{
    unsigned char *empty = malloc(sizeof(unsigned char) * size);

    for (int i = 0; i < size; ++i)
    {
        empty[i] = 0;
    }

    return empty;
}

long *generate_empty_long_array(long size)
{
    long *empty = malloc(sizeof(long) * size);

    for (int i = 0; i < size; ++i)
    {
        empty[i] = 0;
    }

    return empty;
}


long *generate_histogram(unsigned char *image, long size, int number_of_channels)
{
    long *histogram = generate_empty_long_array(MAX_COLOR_VALUE);

    for (int i = 0; i < size * number_of_channels; i += number_of_channels)
    {
        histogram[(int)image[i]]++;
    }

    return histogram;
}

long *get_cumulative_distribution(long *histogram)
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
    return (long) round( (double)(value - minimum) * factor) + 1;
}

long *get_equalized_cumulative_distribution(long *cumulative_distribution, long minimum, long size)
{
    long *equalized_cumulative_distribution = generate_empty_long_array(MAX_COLOR_VALUE);
    double numerator = (double) MAX_COLOR_VALUE - 2;
    double denominator = (double) size - minimum;
    double FACTOR = numerator / denominator;

    for (int i = 0; i < MAX_COLOR_VALUE; ++i)
    {
        equalized_cumulative_distribution[i] = get_equalized_value(cumulative_distribution[i], minimum, FACTOR);
    }

    return equalized_cumulative_distribution;
}

unsigned char *generate_image(unsigned char *original_image, int number_of_channels, long *equalized_cumulative_distribution, long size)
{
    unsigned char *new_image = generate_empty_unsigned_char_array(size * number_of_channels);

    for (int i = 0; i < size * number_of_channels; i++)
    {
        unsigned char original_value = original_image[i];
        if (i % number_of_channels == 0) new_image[i] = (unsigned char) equalized_cumulative_distribution[original_value];
        else new_image[i] = (unsigned char) original_value;
    }

    return new_image;
}
