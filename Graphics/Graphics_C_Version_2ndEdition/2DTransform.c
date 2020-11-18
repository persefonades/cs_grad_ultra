#include <stdio.h>
#include "graphics.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 500

typedef float Matrix3x3[3][3];
Matrix3x3 theMatrix;

void matrix3x3SetIdentity(Matrix3x3 m)
{
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			m[i][j] = (i == j);
}

/* Multiplies matrix a times b, putting result in b */
void matrix3x3PreMultiply(Matrix3x3 a, Matrix3x3 b)
{
	int r, c;
	Matrix3x3 tmp;

	for (r = 0; r < 3; r++)
		for (c = 0; c < 3; c++)
			tmp[r][c] =
			    a[r][0] * b[0][c] + a[r][1] * b[1][c] + a[r][2] * b[2][c];

	for (r = 0; r < 3; r++)
		for (c = 0; c < 3; c++)
			b[r][c] = tmp[r][c];
}

void translate2(int tx, int ty)
{
	Matrix3x3 m;

	matrix3x3SetIdentity(m);
	m[0][2] = tx;
	m[1][2] = ty;
	matrix3x3PreMultiply(m, theMatrix);
}

void scale2(float sx, float sy, wcPt2 refpt)
{
	Matrix3x3 m;

	matrix3x3SetIdentity(m);
	m[0][0] = sx;
	m[0][2] = (1 - sx) * refpt.x;
	m[1][1] = sy;
	m[1][2] = (1 - sy) * refpt.y;
	matrix3x3PreMultiply(m, theMatrix);
}

void rotate2(float a, wcPt2 refPt)
{
	Matrix3x3 m;

	matrix3x3SetIdentity(m);
	a = pToRadians(a);
	m[0][0] = cosf(a);
	m[0][1] = -sinf(a);
	m[0][2] = refPt.x * (1 - cosf(a)) + refPt.y * sinf(a);
	m[1][0] = sinf(a);
	m[1][1] = cosf(a);
	m[1][2] = refPt.y * (1 - cosf(a)) - refPt.x * sinf(a);
	matrix3x3PreMultiply(m, theMatrix);
}

void transformPoints2(int npts, wcPt2 *pts)
{
	int k;
	float tmp;

	for (k = 0; k < npts; k++) {
		tmp = theMatrix[0][0] * pts[k].x + theMatrix[0][1] * pts[k].y
		      + theMatrix[0][2];
		pts[k].y = theMatrix[1][0] * pts[k].x + theMatrix[1][1] * pts[k].y
		           + theMatrix[1][2];
		pts[k].x = tmp;
	}
}


int main(int argc, char const *argv[])
{
	wcPt2 pts[3] = { 50.0, 50.0, 150.0, 50.0, 100.0, 150.0};
	wcPt2 refPt = {100.0, 100.0};

	openGraphics(WINDOW_WIDTH, WINDOW_HEIGHT, "2D Transform");

	setBackground(WHITE);
	setColor(BLUE);
	pFillArea(3, pts);
	matrix3x3SetIdentity(theMatrix);
	scale2(0.5, 0.5, refPt);
	rotate2(90.0, refPt);
	translate2(0, 150);
	transformPoints2(3, pts);
	pFillArea(3, pts);

	// sleep(10);
	getch();
	closeGraphics();
	return 0;
}
