#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"
#define N 3

#define N_EDGE 4

typedef enum {Left, Right, Bottom, Top} Edge;

int inside(wcPt2 p, Edge b, dcPt wMin, dcPt wMax)
{
	switch (b) {
	case Left: if (p.x < wMin.x)return FALSE; break;
	case Right: if (p.x > wMax.x) return FALSE; break;
	case Bottom: if (p.y < wMin.y) return FALSE; break;
	case Top: if (p.y > wMax.y) return FALSE; break;
	}
	return TRUE;
}

int cross(wcPt2 p1, wcPt2 p2, Edge b, dcPt wMin, dcPt wMax)
{
	if (inside(p1, b, wMin, wMax) == inside(p2, b, wMin, wMax))
		return FALSE;
	return TRUE;
}

wcPt2 intersect(wcPt2 p1, wcPt2 p2, Edge b, dcPt wMin, dcPt wMax)
{
	wcPt2 iPt;
	float m;

	if (p1.x != p2.x)m = (p2.y - p1.y) / (p2.x - p1.x);
	switch (b) {
	case Left:
		iPt.x = wMin.x;
		iPt.y = p2.y + (wMin.x - p2.x) * m;
		break;
	case Right:
		iPt.x = wMax.x;
		iPt.y = p2.y + (wMax.x - p2.x) * m;
		break;
	case Bottom:
		iPt.y = wMin.y;
		if (p1.x != p2.x) iPt.x = p2.x + (wMin.y - p2.y) / m;
		else iPt.x = p2.x;
		break;
	case Top:
		iPt.y = wMax.y;
		if (p1.x != p2.x) iPt.x = p2.x + (wMax.y - p2.y) / m;
		else iPt.x = p2.x;
		break;
	}

	return iPt;
}

void clipPoint(wcPt2 p, Edge b, dcPt wMin, dcPt wMax,
               wcPt2 *pOut, int *cnt, wcPt2 *first[], wcPt2 *s)
{
	wcPt2 iPt;

	/* If no previous point exists for this edge, save this point */
	if (!first[b])
		first[b] = &p;
	else
		/* Previous point exists. If 'p' and previous point cross edge,
		find intersection. Clip against next boundary, if any. If no more
		edges, add intersection to output list. */
		if (cross(p, s[b], b, wMin, wMax)) {
			iPt = intersect(p, s[b], b, wMin, wMax);
			if (b < Top)
				clipPoint(iPt, b + 1, wMin, wMax, pOut, cnt, first, s);
			else {
				pOut[*cnt] = iPt; (*cnt)++;
			}
		}
	s[b] = p; /* Save 'p' as most recent point for this edge */

	/* For all, if point is 'inside' proceed to next clip edge, if any */
	if (inside(p, b, wMin, wMax))
		if (b < Top)
			clipPoint(p, b + 1, wMin, wMax, pOut, cnt, first, s);
		else {
			pOut[*cnt] = p; (*cnt)++;
		}
}

void closeClip(dcPt wMin, dcPt wMax, wcPt2 *pOut,
               int *cnt, wcPt2 *first[], wcPt2 *s)
{
	wcPt2 i;
	Edge b;

	for (b = Left; b <= Top; b++) {
		if (cross(s[b], *first[b], b, wMin, wMax)) {
			i = intersect(s[b], *first[b], b, wMin, wMax);
			if (b < Top)
				clipPoint(i, b + 1, wMin, wMax, pOut, cnt, first, s);
			else {
				pOut[*cnt] = i; (*cnt)++;
			}
		}
	}
}

int clipPolygon(dcPt wMin, dcPt wMax, int n, wcPt2 *pIn, wcPt2 *pOut)
{
	/* 'first' holds pointer to first point processed against a clip
	edge. 's' holds most recent point processed against an edge */
	wcPt2 *first[N_EDGE] = {0, 0, 0, 0}, s[N_EDGE];
	int i, cnt = 0;

	for (i = 0; i < n; i++)
		clipPoint(pIn[i], Left, wMin, wMax, pOut, &cnt, first, s);
	closeClip(wMin, wMax, pOut, &cnt, first, s);
	return cnt;
}

float fn(float f)
{
	return (10 + f) * 25;
}

int main(int argc, char **argv)
{
	dcPt winMin = {fn(-3), fn(1)}, winMax = {fn(2), fn(6)};
	// wcPt2 p[4][2];
	wcPt2 p[N_EDGE] = {
		fn(-4), fn(2),
		fn(-1), fn(7),
		fn(-1), fn(5),
		fn(3), fn(8)
	};
	int i;

	openGraphics(600, 600, "Cyrus Beck Algorithm");

	setBackground(WHITE);
	setColor(BLUE);
	drawWindow(winMin, winMax);
	setColor(RED);
	pPolygon(N_EDGE, p);
	setColor(BLACK);
	fprintf(stderr, "%d\n", clipPolygon(winMin, winMax, 4, &p[0], &p[3]) );
	getch();
	closeGraphics();
	return 0;
}