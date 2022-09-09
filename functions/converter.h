#ifndef CONVERTER_H
#define CONVERTER_H

/*formules de wikipÃ©dia : 
pour XYZ : https://en.wikipedia.org/wiki/SRGB#From_sRGB_to_CIE_XYZ
pour LAB : https://en.wikipedia.org/wiki/CIELAB_color_space#From_CIEXYZ_to_CIELAB
*/

#include <cmath>

const double pi = 3.141592653589793;


double gamma_expand(double value);
double gamma_compress(double value);
unsigned char expand_to_byte(double value);


void convert_RGB_to_XYZ(unsigned char *img, double *XYZimg, int w, int h);

void convert_XYZ_to_RGB(unsigned char *oimg, double *XYZimg, int w, int h);

double LABfun(double value);
double LABfun_inv(double value);

void convert_RGB_to_LAB(unsigned char *img, double *XYZimg, int w, int h);

void convert_LAB_to_RGB(unsigned char *oimg, double *LABimg, int w, int h);


void RGB_to_LCH(int R, int G, int B, double *L, double *C, double *H);

void LCH_to_RGB(double l, double C, double H, int *r, int *g, int *b);

void RGB_to_LAB(double *r, double *g, double *b);

void LAB_to_RGB(double *L, double *a, double *b);

void LAB_to_LCH(double *L, double *a, double *b);

void LCH_to_LAB(double *L, double *a, double *b);


#endif //CONVERTER_H
