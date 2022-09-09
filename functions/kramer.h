// CPP program to calculate solutions of linear
// equations using cramer's rule
#include <bits/stdc++.h>
using namespace std;

// This functions finds the determinant of Matrix
double determinantOfMatrix(double mat[3][3]);

// This function finds the solution of system of
// linear equations using cramer's rule
void findSolution(double coeff[3][4], double *outCoeffs);
