// CPP program to calculate solutions of linear
// equations using cramer's rule
#include "kramer.h"
using namespace std;

// This functions finds the determinant of Matrix
double determinantOfMatrix(double mat[3][3])
{
	double ans;
	ans = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2])
		- mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])
		+ mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
	return ans;
}

// This function finds the solution of system of
// linear equations using cramer's rule
void findSolution(double coeff[3][4], double *outCoeffs)
{
	// Matrix d using coeff as given in cramer's rule
	double d[3][3] = {
		{ coeff[0][0], coeff[0][1], coeff[0][2] },
		{ coeff[1][0], coeff[1][1], coeff[1][2] },
		{ coeff[2][0], coeff[2][1], coeff[2][2] },
	};
	// Matrix d1 using coeff as given in cramer's rule
	double d1[3][3] = {
		{ coeff[0][3], coeff[0][1], coeff[0][2] },
		{ coeff[1][3], coeff[1][1], coeff[1][2] },
		{ coeff[2][3], coeff[2][1], coeff[2][2] },
	};
	// Matrix d2 using coeff as given in cramer's rule
	double d2[3][3] = {
		{ coeff[0][0], coeff[0][3], coeff[0][2] },
		{ coeff[1][0], coeff[1][3], coeff[1][2] },
		{ coeff[2][0], coeff[2][3], coeff[2][2] },
	};
	// Matrix d3 using coeff as given in cramer's rule
	double d3[3][3] = {
		{ coeff[0][0], coeff[0][1], coeff[0][3] },
		{ coeff[1][0], coeff[1][1], coeff[1][3] },
		{ coeff[2][0], coeff[2][1], coeff[2][3] },
	};

	// Calculating Determinant of Matrices d, d1, d2, d3
	double D = determinantOfMatrix(d);
	double D1 = determinantOfMatrix(d1);
	double D2 = determinantOfMatrix(d2);
	double D3 = determinantOfMatrix(d3);

	// Case 1
	if (D != 0) {
		// Coeff have a unique solution. Apply Cramer's Rule
		double x = D1 / D;
		double y = D2 / D;
		double z = D3 / D; // calculating z using cramer's rule
		outCoeffs[0]=x;
		outCoeffs[1]=y;
		outCoeffs[2]=z;
	}
	// Case 2
	else {
		if (D1 == 0 && D2 == 0 && D3 == 0)
			printf("Palette vectors are linearly dependent..\n");
		else if (D1 != 0 || D2 != 0 || D3 != 0)
			printf("Palette vectors allow no decomposition of rgb color\n");
	}
}