//
// Created by armau on 28/01/2021.
//

#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION

#include "stb-master/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb-master/stb_image_write.h"

#define MAX_COLOR_VALUE 256

unsigned char *generateHistogram(unsigned char *image, long length, int numberOfChannels);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: main (Ubicacion de la imagen)\n");
        return -1;
    }

    char *imagePath = argv[1];
    int width, height, numberOfChannels;
    unsigned char *image = stbi_load(imagePath, &width, &height, &numberOfChannels, 0);

    if (image == NULL)
    {
        printf("No se pudo abrir la imagen.\n");
        return -1;
    }

    printf("Ubicacion de la imagen: %s\n", imagePath);
    printf("Ancho: %d\n", width);
    printf("Alto: %d\n", height);
    printf("Numero de canales: %d\n", numberOfChannels);

    unsigned char *histogram = generateHistogram(image, width * height, numberOfChannels);

    return 0;
}

unsigned char *generateHistogram(unsigned char *image, long length, int numberOfChannels)
{
    unsigned char *histogram = malloc(sizeof(unsigned char) * MAX_COLOR_VALUE);

    for (int i = 0; i < MAX_COLOR_VALUE; ++i)
    {
        histogram[i] = 0;
    }

    for (int i = numberOfChannels - 1; i < length; ++i)
    {
        histogram[image[i]]++;
    }

    return histogram;
}