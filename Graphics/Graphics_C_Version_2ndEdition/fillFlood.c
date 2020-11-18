#include "graphics.h"


void fillFlood(int x, int y, int fillcolor, int oldcolor)
{
	int current;
	current = getPixel(x, y);
	if (getPixel(x, y) == oldcolor) {
		setColor(fillcolor);
		setPixel(x, y);
		fillFlood(x + 1, y, fillcolor, oldcolor);
		fillFlood(x - 1, y, fillcolor, oldcolor);
		fillFlood(x, y + 1, fillcolor, oldcolor);
		fillFlood(x, y - 1, fillcolor, oldcolor);
	}
}

void loadPolygon()
{
	int n = 4;
	wcPt2 points[n];
	points[0].x = 115;
	points[0].y = 450;
	points[1].x = 425;
	points[1].y = 395;
	points[2].x = 400;
	points[2].y = 150;
	points[3].x = 75;
	points[3].y = 175;
	polygon(n, points);
}

int main(int argc, char **argv)
{
	openGraphics(900, 600, "Flood Fill");

	loadPolygon();

	fillFlood(90, 250, RED, BLACK);

	getchar();

	closeGraphics();

	return 0;
}