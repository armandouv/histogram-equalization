//
// Created by armau on 28/01/2021.
//

#include <stdio.h>
#include <stdlib.h>

#include "image_equalization/equalize_image.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: main (Ubicacion de la imagen)\n");
        return -1;
    }

    return equalize_image(argv[1]);
}
