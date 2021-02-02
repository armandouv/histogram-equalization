//
// Created by armau on 01/02/2021.
//
#include "sequential/equalize_image_sequential.h"
#include "../util/filenames.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../stb-master/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../stb-master/stb_image_write.h"

int equalize_image(char* image_path)
{
    int width, height, number_of_channels;
    unsigned char *image = stbi_load(image_path, &width, &height, &number_of_channels, 0);

    if (image == NULL)
    {
        printf("No se pudo abrir la imagen.\n");
        return -1;
    }

    char *image_name = get_filename(image_path);
    printf("Nombre de la imagen: %s\n", image_name);
    printf("Ancho: %d\n", width);
    printf("Alto: %d\n", height);
    printf("Numero de canales: %d\n", number_of_channels);
    printf("Tamano: %d\n", width * height);

    double sequential_time = equalize_image_sequential(image, width, height, number_of_channels, image_name);

    printf("\nTiempo secuencial: %f\n", sequential_time);

    stbi_image_free(image);
    free(image_name);
    return 0;
}