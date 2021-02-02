//
// Created by armau on 01/02/2021.
//

#ifndef HISTOGRAM_EQUALIZATION_GENERATE_IMAGE_PARALLEL_H
#define HISTOGRAM_EQUALIZATION_GENERATE_IMAGE_PARALLEL_H

void generate_image_parallel(unsigned char *original_image, unsigned char *new_image, int number_of_channels,
                               long *equalized_cumulative_distribution, long size);

#endif //HISTOGRAM_EQUALIZATION_GENERATE_IMAGE_PARALLEL_H
