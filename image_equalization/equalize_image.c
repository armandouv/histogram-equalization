//
// Created by armau on 01/02/2021.
//
#include "sequential/equalize_image_sequential.h"
#include "parallel/equalize_image_parallel.h"
#include "../util/filenames.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../stb-master/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../stb-master/stb_image_write.h"
#include <omp.h>

int equalize_image(char* image_path)
{
    int width, height, number_of_channels;

    double start_load = omp_get_wtime();
    unsigned char *image = stbi_load(image_path, &width, &height, &number_of_channels, 0);
    double end_load = omp_get_wtime();

    if (image == NULL)
    {
        printf("No se pudo abrir la imagen.\n");
        return -1;
    }

    char *image_name = get_filename(image_path);
    printf("Nombre de la imagen: %s\n", image_name);
    printf("Tiempo de carga: %f\n", end_load - start_load);
    printf("Ancho: %d\n", width);
    printf("Alto: %d\n", height);
    printf("Numero de canales: %d\n", number_of_channels);
    printf("Tamano: %d\n", width * height);

    double sequential_time = equalize_image_sequential(image, width, height, number_of_channels, image_name);
    double parallel_time = equalize_image_parallel(image, width, height, number_of_channels, image_name);

    int num_processors = omp_get_num_procs();
    double speedup = sequential_time / parallel_time;
    double efficiency = speedup / num_processors;
    double overhead = parallel_time - sequential_time / num_processors;

    printf("\nNumero de procesadores: %d\n", num_processors);
    printf("Tiempo secuencial: %f\n", sequential_time);
    printf("Tiempo paralelo: %f\n", parallel_time);
    printf("Speedup: %f\n", speedup);
    printf("Eficiencia: %f\n", efficiency);
    printf("Overhead: %f\n", overhead);

    stbi_image_free(image);
    free(image_name);
    return 0;
}