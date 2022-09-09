#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <iostream>
#include "colorOps.h"
#include "harmonie.h"




//img will be overwritten with recomposition according to the "deco" coefficients and the fpalette.
int treatTheImage(unsigned char *img, double *deco, unsigned char *palette, int w,int h);

//decomposes the image into 3, then fills deco with the displayable rgb decompositions, and deco with the decomposition coefficients.
//"deco" must be 3*h*w*3 big, fpalette 9 big, the others w*h*3.
void getDecompositionImages(unsigned char *img, unsigned char *deco, double *fimg, unsigned char *palette,int w,int h);

#endif //TEST_H
