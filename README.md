# histogram-equalization
A program that performs adjustments in contrast levels and expands the intensity range in a digital image.

Compiling from the root directory:\
gcc -fopenmp util/*.c image_equalization/sequential/*.c image_equalization/parallel/*.c image_equalization/equalize_image.c
main.c -o main

Usage: ./main [image_path]\
Plot generation: python generate_plots.py [image_name (without extension, must be located at the root directory)]


