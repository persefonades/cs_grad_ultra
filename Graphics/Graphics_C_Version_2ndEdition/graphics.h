#ifndef GRAPHICS
#define GRAPHICS

#include <string.h>
#include <math.h>
#include <graphics.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct wcPt2 {
	float x, y;
} wcPt2;

typedef struct wcPt3 {
	float x, y, z;
} wcPt3;

typedef struct dcPt {
	float x, y;
} dcPt;

typedef enum {
	MT_CIRCLE, MT_SQUARE, MT_TRIANGLE,
	MT_FCIRCLE, MT_FSQUARE, MT_FTRIANGLE,
	MT_MINUS, MT_PLUS, MT_CROSS, MT_ASTERIX
} pMarkerType;

typedef enum {
	LT_SOLID, LT_DASHED, LT_DOTTED, LT_DASH_DOTTED
} pLineType;

typedef enum {
	FS_HOLLOW, FS_SOLID, FS_PATTERN, FS_HATCH
} pFillStyle;

typedef enum {
	PP_RIGHT, PP_LEFT, PP_UP, PP_DOWN
} pPathPosition;

typedef enum {
	H_LEFT, H_RIGHT, H_CENTER
} pHAlign;

typedef enum {
	V_TOP, V_BOTTOM, V_CAP, V_HALF, V_BASE
} pVAlign;

typedef enum {
	STRING, CHARACTER, STROKE
} txtPrecision;

// Prelim primitives
void setPixel(int x, int y);
int getPixel(int x, int y);

// Curves
void generalizedDrawingPrimitive(int n, wcPt2* wcPoints, int id, int* datalist);

// Line primitives
pLineType pLT = LT_SOLID;
void pPolyline(int n, wcPt2* wcPoints);
void pSetLineType(pLineType lt);
void pSetLineWidthScaleFactor(float lw);
void pSetPolylineColourIndex(int lc);

// Curve primitives
void pSetColourRepresentation(int ws, int ci, int colorptr);

// Fill primitives
void pSetInteriorStyle(pFillStyle fs);
void pSetInteriorColourIndex(int fc);

void pSetInteriorStyleIndex(int pi);
void pSetPatternRepresentation(int ws, int pi, int nx, int ny, int** cp);
void pSetPatternSize(int dx, int dy);
void pSetPatternReferencePoint(wcPt2 position);

// Text primitives
void pSetTextFont(char* tf);
void pSetTextColourIndex(int tc);
void pSetCharacterHeight(int ch);
void pSetCharacterExpansionFactor(int cw);
void pSetCharacterSpacing(int cs);
void pSetCharacterUpVector(wcPt2 upvect);
void pSetTextPath(pPathPosition tp);
void pSetTextAlignment(pHAlign h, pVAlign v);
void pSetTextPrecision(txtPrecision tpr);

// Marker primitives
pMarkerType mT = MT_CIRCLE;
int markerSize = 2;
void pSetMarkerType(pMarkerType mt);
void pSetMarkerSizeScaleFactor(int ms);
void pSetPolymarkerColourIndex(int mc);

// Bundled Primitives
void pSetIndividualASF(int attributeptr, int flagptr);

void pSetPolylineRepresentation(
    int ws, int li, pLineType lt, int lw, int lc
);
void pSetPolylineIndex(int li);

void pSetInteriorRepresentation(int ws, int fi, int fs, int pi, int fc);
void pSetInteriorIndex(int fi);

void pSetTextRepresentation(
    int ws, int ti, int tf, int tp, int te, int ts, int tc
);
void pSetTextIndex(int ti);

void pSetPolymarkerRepresentation(
    int ws, int mi, int mt, int ms, int mc
);
void petPolymarkerIndex(int mi);

// Inquiry functions
void inquirePolylineIndex(int lastli);
void inquireInteriorColourIndex(int lastfc);
void inquireLinetype(int oldlt);

// Output primitives
void pCircle(wcPt2 center, float r);
void pRect(wcPt2 center, float r);
void pRectangle(wcPt2* pts);
void pFillArea(int n, wcPt2* pts);
void pCellArray(wcPt2* pts, int n, int m, int** colors);
void pText(wcPt2 position, char* txt);
void pPolymarker(int n, wcPt2* pts);

// Clipping
// Curve Clipping
// Text clipping
// Exterior clipping

// Transform functions
// void translate(translateVector, matrixTranslate);
// void rotate(theta, matrixRotate);
// void scale(scaleVector, matrixScale);
// void composeMatrix(matrix2, matrix1, matrixOut);
// void buildTransformationMatrix(referencePoint, translateVector,
// 	theta, scaleVector, matrix);
// void composeTransformationMatrix(matrixIn, referencePoint,
// 	translateVector, theta, scaleVector, matrixOut);
// void transformPoint(inPoint, matrix, outPoint);

// Viewing functions
// void evaluateViewOrientationMatrix(x0, y0, xV, yV,
//                                    error, viewMatrix);
// void evaluateViewMappingMatrix(xwmin, xwmax, ywmin, ywmax,
//                                xvmin, xvmax, yvmin, yvmax, error, viewMappingMatrix);
// void setViewRepresentation(ws, viewIndex, viewMatrix, viewMappingMatrix,
//                            xclipmin, xclipmax, yclipmin, yclipmax, clipxy);
// void setViewIndex(viewIndex);
// void setWorkstationWindow(ws, xwsWindmin, xwsWindmax,
//                           ywsWindmin, ywsWindmax);
// void setWorkstationViewport(ws, xwsVPortmin, xwsVPortmax,
//                             ywsVPortmin, ywsVPortmax);

// Structure Primitives
/*
	openStructure(id)
	closeStructure
	postStructure(ws, id, priority)
	unpostStucture(ws, id)
	unpostAllStructures(ws)
	deleteStructure(id)
	deleteAllStructures
	changeStructureIdentifier(oldID, newID)
	setInvisibilityFilter(ws, devCode, invisSet, visSet)
	setHighlightingFilter(ws, devCode, highlightSet,
	nohighlightSet)
	setElementPointer(k)
	offsetElementPointer(dk)
	setEditMode(mode)
	deleteElement
	deleteElementRange(k1,k2)
	emptyStructure(id)
	label(k)
	setElementPointerAtLabel(k)
	deleteElementsBetweenLabels(k1,k2)
	copyAllElementsFromStructure(id)
	executeStructure(id)
	setLocalTransformation(mlt, type)
	deleteStructureNetwork(id)
*/

// void main()
// {
// 	enum {Frame, Wheel, Bicycle};
// 	int nPts;
// 	wcPt2 pts[256];
// 	pMatrix3 m;
// 	/* Routines to generate geometry */
// 	extern void getWheelVertices(int *nPts, wcPt2 pts);
// 	extern void getFrameVertices(int *nPts, wcPt2 pts);

// 	/* Make the wheel structure */
// 	getWheelVertices(nPts, pts);
// 	openStructure(Wheel);
// 	setLineWidth(2.1);
// 	polyline(nPts, pts);
// 	closeStructure;
// 	// /* Make the frame structure */
// 	getFrameVertices(nPts, pts);
// 	openStructure(Frame);
// 	setLineWidth(2.0);
// 	polyline(nPts, pts);
// 	closeStructure;

// 	// /* Make the bicycle */
// 	openStructure(Bicycle);
// 	// /* Include the frame */
// 	executeStructure(Frame);
// 	// /* Position and include rear wheel */
// 	matrixSetIdentity(m);
// 	m[0, 2] := -1.0; m[1, 2] := -0.5;
// 	setLocalTransformationMatrix(m, REPLACE);
// 	executeStructure(Wheel);
// 	/* Position and include front wheel */
// 	m[0,2] := -1.0; m[1,2] := -0.5;
// 	setLocalTransformationMatrix(m, REPLACE);
// 	executeStructure(Wheel);
// 	closeStructure;
// }

// 3D Functions
// void polyline3(int n, wcPt3 *wcPoints);
// void fillarea3(int n, wcPt3 *wcPoints);
// void polyline3(wcPt3 wcPoint, char* string);
// void getLocator3(wcPt3 wcPoint);
// void translate3(translateVector, matrixTranslate);


// Definitions
void setPixel(int x, int y)
{
	putpixel(x, y, getcolor());
}

int getPixel(int x, int y)
{
	return getpixel(x, y);
}

void setColor(int color)
{
	setcolor(color);
	setfontcolor(color);
}

int getColor()
{
	return getcolor();
}

void setBackground(int color)
{
	setbkcolor(color);
}

int getBackground()
{
	return getbkcolor();
}

void openGraphics(
    int width,
    int height,
    char* title
)
{
	int gd = USER, gm = width * 1000 + height;
	initgraph(&gd, &gm, title);
}

void closeGraphics()
{
	closegraph();
}

void polyline(int n, wcPt2* wcPoints)
{
	int i;
	moveto(wcPoints[0].x, wcPoints[0].y);
	for (i = 1; i < n; ++i) {
		lineto(wcPoints[i % n].x, wcPoints[i % n].y);
	}
}

void polygon(int n, wcPt2* wcVertices)
{
	int i;
	moveto(wcVertices[0].x, wcVertices[0].y);
	for (i = 1; i <= n; ++i) {
		lineto(wcVertices[i % n].x, wcVertices[i % n].y);
	}
}

void cellPoints(wcPt2* wcPoints, int n, int m, int** colorArray) {}

void text(wcPt2 wcPoint, char* string) {}

void polymarker(int n, wcPt2* wcPoints)
{
	int i;
	for (i = 0; i < n ; ++i) {
		setPixel(wcPoints[i].x, wcPoints[i].y);
	}
}

void fillArea(int n, wcPt2* wcVertices) {}

// void fillRectangle() {}
// void fillCircle() {}
// void fillCircleArc() {}
// void fillEllipse() {}
// void fillEllipseArc() {}


// void lineDDA(int x1, int y1, int x2, int y2)
// {
// 	int dx = x2 - x1, dy = y2 - y1, steps, k;
// 	float xIncrement, yIncrement, x = x1, y = y1;

// 	if (abs(dx) > abs(dy))
// 		steps = abs(dx);
// 	else
// 		steps = abs(dy);
// 	xIncrement = dx / (float)steps;
// 	yIncrement = dy / (float)steps;

// 	setPixel(round(x), round(y));
// 	for (k = 0; k < steps; k++) {
// 		x += xIncrement;
// 		y += yIncrement;
// 		setPixel(round(x), round(y));
// 	}
// }

void pLine(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1, dy = y2 - y1, steps, k;
	float xIncrement, yIncrement, x = x1, y = y1;

	int linePadding = 4, paddingCounter = 0;

	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	xIncrement = dx / (float)steps;
	yIncrement = dy / (float)steps;

	setPixel(round(x), round(y));
	for (k = 0; k < steps - 1; k++) {
		x += xIncrement;
		y += yIncrement;

		switch (pLT) {
		case LT_SOLID: setPixel(round(x), round(y)); break;
		case LT_DASHED:
			if (paddingCounter % 10 > 4)
				setPixel(round(x), round(y));
			break;
		case LT_DOTTED:
			if (paddingCounter % 6 == 0)
				setPixel(round(x), round(y));
			break;
		case LT_DASH_DOTTED:
			if (paddingCounter % 16 == 0 || (paddingCounter % 16 > 5 && paddingCounter % 16 <= 10))
				setPixel(round(x), round(y));
			break;
		}
		paddingCounter++;
	}
	setPixel(round(x), round(y));
}

void pPolyline(int n, wcPt2 * pts)
{
	int i, x_prev, y_prev;
	if (n > 0) {
		x_prev = pts[0].x; y_prev = pts[0].y;
	}
	for (i = 1; i < n; ++i) {
		pLine(x_prev, y_prev, pts[i % n].x, pts[i % n].y);
		x_prev = pts[i % n].x;
		y_prev = pts[i % n].y;
	}
}

void pSetLineType(pLineType lt)
{
	pLT = lt;
}

void pPolygon(int n, wcPt2 * pts)
{
	int i, x_prev, y_prev;
	if (n > 0) {
		x_prev = pts[0].x; y_prev = pts[0].y;
	}
	for (i = 1; i <= n; ++i) {
		pLine(x_prev, y_prev, pts[i % n].x, pts[i % n].y);
		x_prev = pts[i % n].x;
		y_prev = pts[i % n].y;
	}
}


void pCirclePlotPoints(int xCenter, int yCenter, int x, int y)
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

void pCircle(wcPt2 center, float r)
{
	int x = 0, y = r, p = 1 - r;
	pCirclePlotPoints(center.x, center.y, x, y);
	while (x < y) {
		x++;
		if (p < 0)
			p += 2 * x + 1;
		else {
			y--;
			p += 2 * (x - y) + 1;
		}
		pCirclePlotPoints(center.x, center.y, x, y);
	}
}

void pSquare(wcPt2 center, float r)
{
	float x = center.x, y = center.y;
	wcPt2 pts[4] = {x - r, y - r, x + r, y - r, x + r, y + r, x - r, y + r};
	pPolygon(4, pts);
}


void pFillArea(int n, wcPt2 * pts)
{
	int i;
	int *polypoints = (int*)malloc(2 * n * sizeof(int));
	for (i = 0; i < n; ++i) {
		polypoints[2 * i] = pts[i].x;
		polypoints[2 * i + 1] = pts[i].y;
	}

	for (i = 0; i < 2 * n; ++i) {
		fprintf(stderr, "%d ", polypoints[i]);
	}
	fprintf(stderr, "%d\n", n);
	pPolygon(n, pts);
	// fillpoly(n, polypoints);
}

void pCellArray(wcPt2 * pts, int n, int m, int** colors) {}

void pPolymarker(int n, wcPt2 * pts)
{
	int i;
	for (i = 0; i < n ; ++i) {
		switch (mT) {
		case MT_CIRCLE: pCircle(pts[i], markerSize); break;
		case MT_SQUARE: break;
		}
	}
}

void pText (wcPt2 position, char* txt)
{
	outtextxy(position.x, position.y, txt);
}


float pToRadians(float deg)
{
	return deg * (M_PI / 180);
}

void drawWindow(dcPt winMin, dcPt winMax)
{
	wcPt2 pts[4] = {
		winMin.x, winMin.y, winMax.x, winMin.y,
		winMax.x, winMax.y, winMin.x, winMax.y
	};
	pPolygon(4, pts);
}

#endif