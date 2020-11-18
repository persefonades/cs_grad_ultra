#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#define N 3

/* Bit masks encode a point's position relative to the clip edges. A point's status is encoded by OR'ing together appropriate bit masks
*/
#define LEFT_EDGE 0x1
#define RIGHT_EDGE 0x2
#define BOTTOM_EDGE 0x4
#define TOP_EDGE 0x8

/*
Points encoded as 0000 are completely Inside the clip rectangle;
all others are outside at least one edge. If OR'ing two codes is FALSE (no bits are set in either code), the line can be Accepted. If the AND operation between two codes is TRUE, the line defined by those endpoints is completely outside the clip region and can be Rejected.
*/
#define INSIDE(a) (!a)
#define REJECT(a, b) (a & b)
#define ACCEPT(a, b) (!(a | b))

unsigned char encode(wcPt2 pt, dcPt winMin, dcPt winMax)
{
	unsigned char code = 0x00;

	if (pt.x < winMax.x)
		code = code | LEFT_EDGE;
	if (pt.x > winMax.x)
		code = code | RIGHT_EDGE;
	if (pt.y < winMin.y)
		code = code | BOTTOM_EDGE;
	if (pt.y > winMax.y)
		code = code | TOP_EDGE;
	return code;
}

void swapPts(wcPt2 *p1, wcPt2 *p2)
{
	wcPt2 tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void swapCodes(unsigned char *c1, unsigned char *c2)
{
	unsigned char tmp;
	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

void clipLine(dcPt winMin, dcPt winMax, wcPt2 p1, wcPt2 p2)
{
	unsigned char code1, code2;
	int done = FALSE, draw = FALSE;
	float m;

	while (!done) {
		code1 = encode(p1, winMin, winMax);
		code2 = encode(p2, winMin, winMax);
		if (ACCEPT(code1, code2)) {
			done = TRUE;
			draw = TRUE;
		} else {
			if (REJECT(code1, code2)) {
				done = TRUE;
			} else {
				/* Ensure that p1 is outside window */
				if (INSIDE(code1)) {
					swapPts(&p1, &p2);
					swapCodes(&code1, &code2);
				}
				/* Use slope (m) to find line-clipEdge intersections */
				if (p2.x != p1.x)
					m = (p2.y - p1.y) / (p2.x - p1.x);
				if (code1 & LEFT_EDGE) {
					p1.y += (winMin.x - p1.x) * m;
					p1.x = winMin.x;
				} else {
					if (code1 & RIGHT_EDGE) {
						p1.y += (winMax.x - p1.x) * m;
						p1.x = winMax.x;
					} else {
						if (code1 & BOTTOM_EDGE) {
							/* Need to update p1.x for non-vertical lines only */
							if (p2.x != p1.x)
								p1.x += (winMin.y - p1.y) / m;
							p1.y = winMin.y;
						} else {
							if (code1 & TOP_EDGE) {
								if (p2.x != p1.x)
									p1.x += (winMax.y - p1.y) / m;
								p1.y = winMax.y;
							}
						}
					}
				}
			}
		}
	}
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
