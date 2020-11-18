#include <stdio.h>
#include "graphics.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 500

#define MARGIN_WIDTH 0.05*WINDOW_WIDTH

int readData(char* inFile, float* data)
{
	int fileError = FALSE;
	FILE *fp;
	int month;

	if ((fp = fopen(inFile, "r")) == NULL)
		fileError = TRUE;
	else {
		for (month = 0; month < 12; ++month)
			fscanf(fp, "%f", &data[month]);
		fclose(fp);
	}
	return (fileError);
}

void chartData(float* data, pLineType lineType)
{
	wcPt2 pts[12];
	float monthWidth = (WINDOW_WIDTH - 2 * MARGIN_WIDTH) / 12;
	int i;

	for (i = 0; i < 12; ++i) {
		pts[i].x = MARGIN_WIDTH + i * monthWidth + 0.5 * monthWidth;
		pts[i].y = data[i];
	}
	pSetLineType(lineType);
	pPolyline(12, pts);
	pPolymarker(12, pts);
}

int main(int argc, char const *argv[])
{
	float data[12];

	openGraphics(WINDOW_WIDTH, WINDOW_HEIGHT, "Line Chart");
	setBackground(WHITE);
	setColor(BLUE);
	readData("data/data1960", data);
	chartData(data, LT_SOLID);
	readData("data/data1970", data);
	chartData(data, LT_DASHED);
	readData("data/data1980", data);
	chartData(data, LT_DOTTED);
	readData("data/data1990", data);
	chartData(data, LT_DASH_DOTTED);
	// sleep(10);
	getch();
	closeGraphics();
	return 0;
}