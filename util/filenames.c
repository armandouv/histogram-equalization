//
// Created by armau on 01/02/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_filename(char *path)
{
    char *filename = strrchr(path, '/');
    if (filename == NULL) filename = path;
    else filename++;
    return strtok(filename, ".");
}

char *generate_new_filename(char *original, char *suffix)
{
    char *new_filename = malloc(sizeof(char) * 1000);
    snprintf(new_filename, sizeof(char) * 1000, "%s%s", original, suffix);
    return new_filename;
}