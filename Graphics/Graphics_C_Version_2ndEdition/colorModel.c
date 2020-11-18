#include <math.h>
#include <stdio.h>

#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)
#define NO_HUE -1

typedef struct hsv {
	double h, s, v;
} hsv;

typedef struct rgb {
	double r, g, b;
} rgb;

typedef struct yiq {
	double y, i, q;
} yiq;

typedef struct cmy {
	double c, m, y;
} cmy;

void hsvToRgb(hsv* hsvColor, rgb* rgbColor)
{
	int i;
	double h = hsvColor->h, s = hsvColor->s, v = hsvColor->v;
	double aa, bb, cc, f;
	if (s == 0) /* Grayscale */
		rgbColor->r = rgbColor->g = rgbColor->b = v;
	else {
		if (h == 1.0) h = 0;
		h *= 6.0;
		i = floor(h);
		f = h - i;
		aa = v * (1 - s);
		bb = v * (1 - (s * f));
		cc = v * (1 - (s * (1 - f)));
		switch (i) {
		case 0: rgbColor->r = v;
			rgbColor->g = cc;
			rgbColor->b = aa;
			break;
		case 1: rgbColor->r = bb;
			rgbColor->g = v;
			rgbColor->b = aa;
			break;
		case 2: rgbColor->r = aa;
			rgbColor->g = v;
			rgbColor->b = cc;
			break;
		case 3:  rgbColor->r = aa;
			rgbColor->g = bb;
			rgbColor->b = v;
			break;
		case 4: rgbColor->r = cc;
			rgbColor->g = aa;
			rgbColor->b = v;
			break;
		case 5: rgbColor->r = v;
			rgbColor->g = aa;
			rgbColor->b = bb;
			break;
		}
	}
}

void rgbToHsv(rgb* rgbColor, hsv* hsvColor)
{
	double r = rgbColor->r, g = rgbColor->g, b = rgbColor->b;
	double max = MAX(r, MAX(g, b)), min = MIN(r, MIN(g, b));
	double delta = max - min;

	hsvColor->v = max;
	if (max != 0.0)
		hsvColor->s = delta / max;
	else
		hsvColor->s = 0.0;
	if (hsvColor->s == 0.0) hsvColor->h = NO_HUE;
	else {
		if (r == max) hsvColor->h = (g - b) / delta;
		else if (g == max) hsvColor->h = 2 + (b - r) / delta;
		else if (b == max) hsvColor->h = 4 + (r - g) / delta;
		hsvColor->h *= 60.0;
		if (hsvColor->h < 0) hsvColor->h += 360.0;
		hsvColor->h /= 360.0;
	}
}

void yiqToRgb(yiq* yiqColor, rgb* rgbColor)
{
	double y = yiqColor->y, i = yiqColor->i, q = yiqColor->q;
	rgbColor->r = y + 0.956 * i + 0.620 * q;
	rgbColor->g = y - 0.272 * i - 0.647 * q;
	rgbColor->b = y - 1.108 * i + 1.705 * q;
}

void rgbToYiq(rgb* rgbColor, yiq* yiqColor)
{
	double r = rgbColor->r, g = rgbColor->g, b = rgbColor->b;
	yiqColor->y = 0.299 * r + 0.587 * g + 0.144 * b;
	yiqColor->i = 0.596 * r - 0.275 * g - 0.321 * b;
	yiqColor->q = 0.212 * r - 0.528 * g + 0.311 * b;
}

void rgbToCmy(rgb* rgbColor, cmy* cmyColor)
{
	cmyColor->c = 1 - rgbColor->r;
	cmyColor->m = 1 - rgbColor->g;
	cmyColor->y = 1 - rgbColor->b;
}

void cmyToRgb(cmy* cmyColor, rgb* rgbColor)
{
	rgbColor->r = 1 - cmyColor->c;
	rgbColor->g = 1 - cmyColor->m;
	rgbColor->b = 1 - cmyColor->y;
}

int main(int argc, char const *argv[])
{
	hsv hsvColor = {0.0, 1.0, 1.0};
	rgb rgbColor = {1.0, 0.0, 0.0};
	yiq yiqColor = {0.0, 0.0, 0.0};
	hsvToRgb(&hsvColor, &rgbColor);
	// printf("hsvToRgb(%lf, %lf, %lf) = (%lf, %lf, %lf)\n",
	//        hsvColor.h, hsvColor.s, hsvColor.v,
	//        rgbColor.r, rgbColor.g, rgbColor.b);
	printf("rgbToHsv(%lf, %lf, %lf) = (%lf, %lf, %lf)\n",
	       rgbColor.r, rgbColor.g, rgbColor.b,
	       hsvColor.h, hsvColor.s, hsvColor.v);
	return 0;
}
