#ifndef COLOROPS_H
#define COLOROPS_H

#include <iostream>
#include "kramer.h"
#include "converter.h"

//forcément palette de 3 couleurs
void decompose_color(double *outCoeffs, double *color, double *palette);

void decompose_image(double *img, double *oimg, double *palette, int w, int h);



void recompose_image(double *coeffImg, double *oimg, double *palette, int w, int h);


void fully_recompose_image(unsigned char *original_img, double *fimg, double *foimg, double *npalette, int w, int h);

#endif  //COLOROPS_H
