#include <stdio.h>
#include <math.h>
#include "graphics.h"

#define TWO_PI 6.28

/* Limacon equation is r=a*cos(theta)*b. Cardioid is the same,
 with a==b, so r=a*(1+cos(theta))
*/

typedef enum {spiral, cardioid, threeLeaf, fourLeaf, limacon} Fig;

void drawCurlyFig(Fig figure, wcPt2 pos, int* p)
{
	float r, theta = 0.0, dtheta = 1.0 / (float)p[0];
	int nPoints = (int) ceilf(TWO_PI * p[0]) + 1;
	wcPt2 *pt;

	if ((pt = (wcPt2*)malloc (nPoints * sizeof(wcPt2))) == NULL) {
		fprintf(stderr, "Couldn't allocate points\n");
		return;
	}

	/* Set first point for figure */
	pt[0].y = pos.y;
	switch (figure) {
	case spiral: pt[0].x = pos.x; break;
	case limacon: pt[0].x = pos.x + p[0] + p[1]; break;
	case cardioid: pt[0].x = pos.x + p[0] * 2; break;
	case threeLeaf: pt[0].x = pos.x + p[0]; break;
	case fourLeaf: pt[0].x = pos.x + p[0]; break;
	}
	nPoints = 1;
	while (theta < TWO_PI) {
		switch (figure) {
		case spiral: r = p[0] * theta; break;
		case limacon: r = p[0] * cosf(theta) + p[1]; break;
		case cardioid: r = p[0] * (1 + cosf(theta)); break;
		case threeLeaf: r = p[0] * cosf(3 * theta); break;
		case fourLeaf: r = p[0] * cosf(2 * theta); break;
		}
		pt[nPoints].x = pos.x + r * cosf(theta);
		pt[nPoints].y = pos.y + r * sinf(theta);
		nPoints++;
		theta += dtheta;
	}

	pPolyline(nPoints, pt);
	free(pt);
}

int main(int argc, char const *argv[])
{
	openGraphics(400, 100, "Draw Shape Figure");
	Fig f;
	/* Center positions for each figure */
	wcPt2 center[] = {50, 50, 100, 50, 175, 50, 250, 50, 300, 50};

	/* Parameters to define each figure. First four need one parameter.
	Fifth figure (limacon) needs two. */
	int p[5][2] = {5, -1, 20, -1, 30, -1, 30, -1, 40, 10};

	setBackground(WHITE);
	setColor(BLACK);
	for (f = spiral; f <= limacon; ++f)
		drawCurlyFig(f, center[f], p[f]);
	sleep(10);
	closeGraphics();
	return 0;
}