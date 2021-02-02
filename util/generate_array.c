//
// Created by armau on 01/02/2021.
//

#include <stdlib.h>

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