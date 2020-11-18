#include "graphics.h"

void circlePlotPoints(int, int, int, int);

void circleBres(int xc, int yc, int r)
{
	int x = 0, y = r, p = 3 - 2 * r;
	circlePlotPoints(xc, yc, x, y);
	while (x < y) {
		if (p < 0) {
			x++;
			p = p + 4 * x + 6;
		} else {
			x++;
			y--;
			p = p + 4 * (x - y) + 10;
		}
		circlePlotPoints(xc, yc, x, y);
	}
}


void circlePlotPoints(int xCenter, int yCenter, int x, int y)
{
	setPixel(xCenter + x, yCenter + y);
	setPixel(xCenter - x, yCenter + y);
	setPixel(xCenter + x, yCenter - y);
	setPixel(xCenter - x, yCenter - y);
	setPixel(xCenter + y, yCenter + x);
	setPixel(xCenter - y, yCenter + x);
	setPixel(xCenter + y, yCenter - x);
	setPixel(xCenter - y, yCenter - x);
}

int main(int argc, char **argv)
{
	openGraphics(900, 600, "Bresenham Circle");

	circleBres(100, 100, 90);

	getchar();

	closeGraphics();

	return 0;
}