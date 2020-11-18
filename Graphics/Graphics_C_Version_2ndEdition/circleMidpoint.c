#include "graphics.h"

void circlePlotPoints(int, int, int, int);

void circleMidpoint(int xCenter, int yCenter, int r)
{
	int x = 0, y = r, p = 1 - r;
	circlePlotPoints(xCenter, yCenter, x, y);
	while (x < y) {
		x++;
		if (p < 0)
			p += 2 * x + 1;
		else {
			y--;
			p += 2 * (x - y) + 1;
		}
		circlePlotPoints(xCenter, yCenter, x, y);
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
	openGraphics(900, 600, "Midpoint Circle");

	circleMidpoint(100, 100, 90);

	getchar();

	closeGraphics();
	return 0;
}