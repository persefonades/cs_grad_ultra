#include <stdio.h>
#include "graphics.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 500
/* Amount of space to leave on each side of the chart */
#define MARGIN_WIDTH 0.05 * WINDOW_WIDTH
#define N_DATA 12

#define TWO_PI 6.28

typedef enum {
	Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
} Months;

char* monthNames[N_DATA] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

int readData(char* inFile, float* data)
{
	int fileError = FALSE;
	FILE *fp;
	Months month;

	if ((fp = fopen(inFile, "r")) == NULL)
		fileError = TRUE;
	else {
		for (month = Jan; month <= Dec; ++month)
			fscanf(fp, "%f", &data[month]);
		fclose(fp);
	}
	return (fileError);
}

void lineChart(float* data)
{
	wcPt2 dataPos[N_DATA], labelPos;
	Months m;
	float mWidth = (WINDOW_WIDTH - 2 * MARGIN_WIDTH) / N_DATA;
	int chartBottom = 0.1 * WINDOW_HEIGHT;
	int offset = 0.05 * WINDOW_HEIGHT; /* Space between data and labels */
	int labelLength = 24; /* Assuming fixed-width 8-pixel characters */

	labelPos.y = chartBottom;
	for (m = Jan; m <= Dec; ++m) {
		/* Calculate x and y positions for data markers */
		dataPos[m].x = MARGIN_WIDTH + m * mWidth + 0.5 * mWidth;
		dataPos[m].y = chartBottom + offset + data[m];
		/* Shift the label to the left by one-half its length */
		labelPos.x = dataPos[m].x - 0.5 * labelLength;
		pText(labelPos, monthNames[m]);
	}
	pPolyline(N_DATA, dataPos);
	pPolymarker(N_DATA, dataPos);
}

void barChart(float* data)
{
	wcPt2 dataPos[4], labelPos;
	Months m;
	float x, mWidth = (WINDOW_WIDTH - 2 * MARGIN_WIDTH) / N_DATA;
	int charBottom = 0.1 * WINDOW_HEIGHT;
	int offset = 0.05 * WINDOW_HEIGHT; /* Space between data and labels */
	int labelLength = 24;

	labelPos.y = charBottom;
	for (m = Jan; m <= Dec; m++) {
		/* Find the center of this month's bar */
		x = MARGIN_WIDTH + m * mWidth + 0.5 * mWidth;

		/* Shift the label to the left by one-half its assumed length */
		labelPos.x = x - 0.5 * labelLength;

		pText(labelPos, monthNames[m]);

		/* Get the coordinates for this month's bar */
		dataPos[0].x = dataPos[3].x = x - 0.5 * labelLength;
		dataPos[1].x = dataPos[2].x = x + 0.5 * labelLength;
		dataPos[0].y = dataPos[1].y = charBottom + offset;
		dataPos[2].y = dataPos[3].y = charBottom + offset + data[m];
		pFillArea(4, dataPos);
	}
}

void pieChart(float* data)
{
	wcPt2 pts[2], center;
	float radius = WINDOW_HEIGHT / 4.0;
	float newSlice, total = 0.0, lastSlice = 0.0;
	Months month;

	center.x = WINDOW_WIDTH / 2;
	center.y = WINDOW_HEIGHT / 2;
	pCircle(center, radius);
	for (month = Jan; month <= Dec; month++)
		total += data[month];
	pts[0].x = center.x; pts[0].y = center.y;
	for (month = Jan; month <= Dec; month++) {
		newSlice = TWO_PI * data[month] / total + lastSlice;
		pts[1].x = center.x + radius * cosf(newSlice);
		pts[1].y = center.y + radius * sinf(newSlice);
		pPolyline(2, pts);
		lastSlice = newSlice;
	}
}

int main(int argc, char **argv)
{
	float data[N_DATA];
	int dataError = 0;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s dataFileName\n", argv[0]);
		exit(0);
	}

	dataError = readData(argv[1], data);
	if (dataError) {
		fprintf(stderr, "Error. Can't read file %s\n", argv[1]);
		exit(0);
	}

	openGraphics(WINDOW_WIDTH, WINDOW_HEIGHT, "Chart");
	setBackground(WHITE);
	setColor(BLACK);
	lineChart(data);
	sleep(10);
	closeGraphics();
	return 0;
}