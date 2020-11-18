#include "graphics.h"

void lineMidpoint(int xa, int ya, int xb, int yb)
{
	int dx = abs(xa - xb), dy = abs(ya - yb);
	int p = dy - dx / 2;
	int x, y, xEnd;
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
			p += dy;
		else {
			y++;
			p += dy - dx;
		}
		setPixel(x, y);
	}
}

int main(int argc, char **argv)
{

	openGraphics(900, 600, "Midpoint Line");

	lineMidpoint(100, 200, 430, 300);

	getchar();

	closeGraphics();
	return 0;
}