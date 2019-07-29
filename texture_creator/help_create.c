/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 20:00:42 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/29 20:29:51 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_creator.h"

int		pick_color(t_data *data, int x, int y)
{
	data->selected_color = data->pixel[SCREEN_W * y + x];
	return (1);
}

int		draw_grid(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < SCREEN_H)
	{
		j = 0;
		while (j < SCREEN_W)
		{
			if (i % data->pixel_size == 0 || j % data->pixel_size == 0)
				data->pixel[SCREEN_W * j + i] = 0x303030;
			j++;
		}
		i++;
	}
	return (0);
}

int		rgb_compose(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | (b));
}

int		rgb_split(int rgb, int *r, int *g, int *b)
{
	*r = (rgb >> 16) & 0xff;
	*g = (rgb >> 8) & 0xff;
	*b = rgb & 0xff;
	return (1);
}

int		rgb_add(int rgb, int rr, int gg, int bb)
{
	int r;
	int g;
	int b;

	rgb_split(rgb, &r, &g, &b);
	r = (int)clamp((int)((float)r + rr), 0, 255);
	g = (int)clamp((int)((float)g + gg), 0, 255);
	b = (int)clamp((int)((float)b + bb), 0, 255);
	return (rgb_compose(r, g, b));
}
