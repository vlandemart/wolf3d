#include "main.h"

/*
**	Splits RGB value into 3 separate ints.
**	Returns 1.
*/
int	rgb_split(int rgb, int *r, int *g, int *b)
{
	*r = (rgb >> 16) & 0xff;
	*g = (rgb >> 8) & 0xff;
	*b = rgb & 0xff;

	return (1);
}

/*
**	Composes RGB value from 3 ints.
**	Returns composed value.
*/
int	rgb_compose(int r, int g, int b)
{
	int rgb;

	rgb = 0;
	rgb = rgb | (r << 16);
	rgb = rgb | (g << 8);
	rgb = rgb | b;
	//printf("%d-%d-%d composed as %d, or %d\n", r, g, b, ((r << 16) | (g << 8) | b), rgb);
	return ((r << 16) | (g << 8) | b);
}

/*
**	Adds value to every color of RGB.
**	Returns resulted RGB.
**	Each color is clamped between 0 and 255.
*/
int	rgb_add(int rgb, float value)
{
	int r;
	int g;
	int b;

	rgb_split(rgb, &r, &g, &b);
	r = CLAMP((int)((float)r + value), 0, 255);
	g = CLAMP((int)((float)g + value), 0, 255);
	b = CLAMP((int)((float)b + value), 0, 255);
	rgb = rgb_compose(r, g, b);
	return (rgb);
}

/*
**	Multiplies each color of RGB by value.
**	Returns resulted RGB.
**	Each color is clamped between 0 and 255.
*/
int	rgb_multiply(int rgb, float value)
{
	int r;
	int g;
	int b;

	rgb_split(rgb, &r, &g, &b);
	//printf("sent %d, split into %d-%d-%d\n", rgb, r, g, b);
	r = CLAMP((int)((float)r * value), 0, 255);
	g = CLAMP((int)((float)g * value), 0, 255);
	b = CLAMP((int)((float)b * value), 0, 255);
	//printf("rgb is %d-%d-%d\n", r, g, b);
	rgb = rgb_compose(r, g, b);
	return (rgb);
}

int	rgb_merge(int rgb1, int rgb2)
{
	int r1;
	int g1;
	int b1;
	int r2;
	int g2;
	int b2;

	rgb_split(rgb1, &r1, &g1, &b1);
	rgb_split(rgb2, &r2, &g2, &b2);
	r1 = CLAMP(r1 + r2, 0, 255);
	g1 = CLAMP(g1 + g2, 0, 255);
	b1 = CLAMP(b1 + b2, 0, 255);
	rgb1 = rgb_compose(r1, g1, b1);
	return (rgb1);
}

/*
**	Blends two RGB values on some percent.
**	Returns resulted RGB.
**	Each color is clamped between 0 and 255.
*/
int	rgb_mix(int rgb1, int rgb2, float percent)
{
	float percent2;

	percent = CLAMP(percent, 0, 1);
	percent2 = 1 - percent;
	rgb1 = rgb_multiply(rgb1, percent);
	rgb2 = rgb_multiply(rgb2, percent2);
	return (rgb_merge(rgb1, rgb2));
}