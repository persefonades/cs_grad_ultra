#include "graphics.h"

void lineBres(int xa, int ya, int xb, int yb)
{
	int dx = abs(xa - xb), dy = abs(ya - yb);
	int p = 2 * dy - dx;
	int twoDy = 2 * dy, twoDyDx = 2 * (dy - dx);
	int x, y, xEnd;

	/* Determine which point to use as start, which as end */
	if (xa > xb) {
		x = xb;
		y = yb;
		xEnd = xa;
	} else {
		x = xa;
		y = ya;
		xEnd = xb;
	}

	setPixel(x, y);
	while (x < xEnd) {
		x++;
		if (p < 0)
			p += twoDy;
		else {
			y++;
			p += twoDyDx;
		}
		setPixel(x, y);
	}
}

int main(int argc, char **argv)
{
	openGraphics(900, 600, "Bresenham Line");

	lineBres(200, 100, 300, 600);

	getchar();

	closeGraphics();
	return 0;
}
