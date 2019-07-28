/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_manipulations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 22:14:22 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 22:38:26 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
**	Adds value to every color of RGB.
**	Returns resulted RGB.
**	Color values are clamped betweed 0 and 255.
*/

int	rgb_add(int rgb, float value)
{
	return (((int)clamp((int)(((rgb >> 16) & 0xff) + value),
					0, 255) << 16) |
			((int)clamp((int)(((rgb >> 8) & 0xff) + value),
				0, 255) << 8) |
			(int)clamp((int)((rgb & 0xff) + value),
				0, 255));
}

/*
**	Multiplies each color of RGB by value.
**	Returns resulted RGB.
**	Color values are clamped betweed 0 and 255.
*/

int	rgb_multiply(int rgb, float value)
{
	return (((int)clamp((int)(((rgb >> 16) & 0xff) * value),
					0, 255) << 16) |
			((int)clamp((int)(((rgb >> 8) & 0xff) * value),
				0, 255) << 8) |
			(int)clamp((int)((rgb & 0xff) * value),
				0, 255));
}

/*
**	Blends two RGB values on some percent.
**	Returns resulted RGB.
*/

int	rgb_mix(int rgb1, int rgb2, float percent)
{
	float percent2;

	percent = clamp(percent, 0, 1);
	percent2 = 1 - percent;
	rgb1 = ((int)(((rgb1 >> 16) & 0xff) * percent +
				((rgb2 >> 16) & 0xff) * percent2) << 16) |
			((int)(((rgb1 >> 8) & 0xff) * percent +
				((rgb2 >> 8) & 0xff) * percent2) << 8) |
			((int)((rgb1 & 0xff) * percent +
				(rgb2 & 0xff) * percent2));
	return (rgb1);
}
