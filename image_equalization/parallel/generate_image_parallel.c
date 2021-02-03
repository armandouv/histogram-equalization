//
// Created by armau on 01/02/2021.
//

void generate_image_parallel(unsigned char *original_image, unsigned char *new_image, int number_of_channels, long *equalized_cumulative_distribution, long size)
{
    #pragma omp parallel for
    for (int i = 0; i < size * number_of_channels; i++)
    {
        unsigned char original_value = original_image[i];
        for (int j = i; j < number_of_channels + i; ++j)
        {
            new_image[i] = (unsigned char) equalized_cumulative_distribution[original_value];
        }
    }
}