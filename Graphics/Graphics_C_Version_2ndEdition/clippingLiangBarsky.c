#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"
#define N 3

int clipTest(float p, float q, float *u1, float *u2)
{
	float r;
	int retVal = TRUE;

	if (p < 0.0) {
		r = q / p;
		if (r > *u2)
			retVal = FALSE;
		else {
			if (r > *u1)
				*u1 = r;
		}
	} else {
		if (p > 0.0) {
			r = q / p;
			if (r < *u1)
				retVal = FALSE;
			else if (r < *u2)
				*u2 = r;
		} else
			/* p=0, so line is parallel to this clipping edge */
			if (q < 0.0)
				/* Line is outside clipping edge */
				retVal = FALSE;
	}
	return retVal;
}

void clipLine(dcPt winMin, dcPt winMax, wcPt2 p1, wcPt2 p2)
{
	float u1 = 0.0, u2 = 1.0, dx = p2.x - p1.x, dy;

	if (clipTest(-dx, p1.x - winMin.x, &u1, &u2))
		if (clipTest(dx, winMax.x - p1.x, &u1, &u2)) {
			dy = p2.y - p1.y;
			if (clipTest(-dy, p1.y - winMin.y, &u1, &u2))
				if (clipTest(dy, winMax.y - p1.y, &u1, &u2)) {
					if (u2 < 1.0) {
						p2.x = p1.x + u2 * dx;
						p2.y = p1.y + u2 * dy;
					}
					if (u1 > 0.0) {
						p1.x += u1 * dx;
						p1.y += u1 * dy;
					}
					pLine(round(p1.x), round(p1.y), round(p2.x), round(p2.y));
				}
		}
}

float fn(float f)
{
	return (10 + f) * 25;
}

int main(int argc, char **argv)
{
	dcPt winMin = {fn(-3), fn(1)}, winMax = {fn(2), fn(6)};
	// wcPt2 p[4][2];
	wcPt2 p[N][2] = {
		{fn(-4), fn(2), fn(-1), fn(7)},
		{fn(-1), fn(5), fn(3), fn(8)},
		{fn(-2), fn(3), fn(1), fn(2)}
	};
	int i;

	openGraphics(600, 600, "Liang Barsky Algorithm");

	setBackground(WHITE);
	setColor(BLUE);
	drawWindow(winMin, winMax);
	setColor(RED);
	for (i = 0; i < N; i++)
		pPolyline(2, p[i]);
	setColor(BLACK);
	for (i = 0; i < N; i++)
		clipLine(winMin, winMax, p[i][0], p[i][1]);

	getch();
	closeGraphics();
	return 0;
}