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