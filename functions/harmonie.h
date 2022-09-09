#ifndef HARMONIE_H
#define HARMONIE_H
#include <cmath>
#include <iostream>
#include "converter.h"
double hue_distance(double hue1, double hue2);
double norm_in_palette(double *paletteLoc);

void normalize_in_palette(double *paletteLoc);

void make_palette_image_array(unsigned char *img, unsigned char *palette, int nbColors);

//will be of size w*(3*h) (pixels)
void make_decomposition_images(double *coeff_img, unsigned char *oimg, double *fpalette, int w, int h);

void move_hue_towards_hue(double *hstart, double hend, int amount);

void harmonize_monochromatic(int max_cluster, int second_cluster, int smallest_cluster, double *hues, int rotation);

void harmonize_complementary(int max_cluster, int second_cluster, int smallest_cluster, double *hues, int rotation);

void harmonize_triadic(int max_cluster, int second_cluster, int smallest_cluster, double *hues, int rotation);



void harmonize_palette(double *fpalette, int *freq);

#endif  //HARMONIE_H
