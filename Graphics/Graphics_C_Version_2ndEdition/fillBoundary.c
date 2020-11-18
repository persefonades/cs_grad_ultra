#include "graphics.h"

void fillBoundary(int x, int y, int fill, int boundary)
{
	int current;
	current = getPixel(x, y);
	if ((current != boundary) && (current != fill)) {
		setColor(fill);
		setPixel(x, y);
		fillBoundary(x + 1, y, fill, boundary);
		fillBoundary(x - 1, y, fill, boundary);
		fillBoundary(x, y + 1, fill, boundary);
		fillBoundary(x, y - 1, fill, boundary);
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
	openGraphics(900, 600, "Boundary Fill");

	loadPolygon();

	fillBoundary(90, 250, BLUE, WHITE);

	getchar();

	closeGraphics();

	return 0;
}