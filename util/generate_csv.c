//
// Created by armau on 01/02/2021.
//
#include <stdio.h>
#include "constants.h"
#include "filenames.h"

void generate_csv(long *original_histogram, long *equalized_histogram, char *image_name, char* suffix)
{
    char *filename = generate_new_filename("out/", image_name);
    filename = generate_new_filename(filename, "_histogram");
    filename = generate_new_filename(filename, suffix);
    filename = generate_new_filename(filename, ".csv");
    FILE *csv = fopen(filename, "w+");

    for (int i = 0; i < MAX_COLOR_VALUE; i++)
        fprintf(csv, "%d,%ld,%ld\n", i, original_histogram[i], equalized_histogram[i]);

    fclose(csv);
}