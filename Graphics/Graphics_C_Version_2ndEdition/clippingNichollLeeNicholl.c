#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#define N 3


void clipLine(dcPt winMin, dcPt winMax, wcPt2 p1, wcPt2 p2)
{
	unsigned char code1, code2;
	int done = FALSE, draw = FALSE;
	float m;


	if (draw) {
		fprintf(stderr, "draw \n");
		pLine(round(p1.x), round(p1.y), round(p2.x), round(p2.y));
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

	openGraphics(600, 600, "Cohen Sutherland");

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
