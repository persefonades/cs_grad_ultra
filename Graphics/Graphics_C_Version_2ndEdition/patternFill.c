#include "graphics.h"

#define WS 1

void patternFill()
{
	wcPt2 pts[4];
	int bwPattern[3][3] = {1, 0, 0, 0, 1, 1, 1, 0, 0};

	pSetPatternRepresentation(WS, 8, 3, 3, bwPattern);

	pts[0].x = 10; pts[0].y = 10;
	pts[1].x = 20; pts[1].y = 10;
	pts[2].x = 28; pts[2].y = 18;
	pts[3].x = 18; pts[3].y = 18;

	pSetInteriorStyle(PATTERN);
	pSetInteriorStyleIndex(8);
	pSetPatternReferencePoint({14, 11});

	pFillArea(4, pts);
}