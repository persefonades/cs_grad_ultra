#include "graphics.h"

void ellipsePlotPoints(int, int, int, int);

void ellipseMidpoint(int xCenter, int yCenter, int rx, int ry)
{
	int rx2 = rx * rx, ry2 = ry * ry;
	int tworx2 = 2 * rx2, twory2 = 2 * ry2;
	int p, x = 0, y = ry, px = 0, py = tworx2 * y;
	ellipsePlotPoints(xCenter, yCenter, x, y);

	// Region 1
	p = round(ry2 - (rx2 * ry) + (0.25 * rx2));
	while (px < py) {
		x++;
		px += twory2;
		if (p < 0)
			p += ry2 + px;
		else {
			y--;
			py -= tworx2;
			p += ry2 + (px - py);
		}
		ellipsePlotPoints(xCenter, yCenter, x, y);
	}

	// Region 2
	p = round(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2);
	while (y > 0) {
		y--;
		py -= tworx2;
		if (p > 0)
			p += rx2 - py;
		else {
			x++;
			px += twory2;
			p += rx2 - py + px;
		}
		ellipsePlotPoints(xCenter, yCenter, x, y);
	}
}

void ellipsePlotPoints(int xCenter, int yCenter, int x, int y)
{
	setPixel(xCenter + x, yCenter + y);
	setPixel(xCenter - x, yCenter + y);
	setPixel(xCenter + x, yCenter - y);
	setPixel(xCenter - x, yCenter - y);
}

int main(int argc, char **argv)
{
	openGraphics(900, 600, "Midpoint Ellipse");

	ellipseMidpoint(250, 180, 150, 75);

	getchar();

	closeGraphics();
	return 0;
}