//
// Created by armau on 01/02/2021.
//

#ifndef HISTOGRAM_EQUALIZATION_CUMULATIVE_DISTRIBUTION_SEQUENTIAL_H
#define HISTOGRAM_EQUALIZATION_CUMULATIVE_DISTRIBUTION_SEQUENTIAL_H

void get_cumulative_distribution_sequential(long *cumulative_distribution, long *histogram);
void get_equalized_cumulative_distribution_sequential(long *cumulative_distribution, long minimum, long size);

#endif //HISTOGRAM_EQUALIZATION_CUMULATIVE_DISTRIBUTION_SEQUENTIAL_H
