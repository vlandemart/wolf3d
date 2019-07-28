/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:34:38 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 22:17:50 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	render(t_wf *wf)
{
	ft_memset(wf->sdl->pix, 0, wf->width * wf->height * sizeof(Uint32));
	ft_memset(wf->zbuf, 0, wf->width * wf->height * sizeof(Uint32));
	movement(wf);
	draw_walls(wf);
	draw_ceilfloor(wf);
	draw_objects(wf);
	update(wf, 0);
}

void	put_pixel(t_wf *wf, t_pix pix)
{
	float	shading;
	int		col;

	if (pix.index < 0 || pix.index > wf->height * wf->width ||
			pix.color == 0xff00ff)
		return ;
	if (pix.zbuf)
	{
		if (wf->zbuf[pix.index] != 0 && wf->zbuf[pix.index] < pix.dist)
			return ;
		wf->zbuf[pix.index] = pix.dist;
	}
	if (pix.wall)
		shading = 1 - (min(pix.dist, wf->light_distance) / wf->light_distance);
	else
		shading = 1 - (min(pix.dist, wf->light_distance * 0.75) /
				(wf->light_distance * 0.75));
	col = rgb_multiply(pix.color, shading);
	if (wf->flash > 0)
		col = rgb_mix(0xffff00, col, wf->flash);
	wf->sdl->pix[pix.index] = col;
}

void	floor_and_ceiling(t_wf *wf)
{
	int		i;
	int		j;
	int		color;

	color = 0;
	i = 0;
	while (i < wf->width)
	{
		j = 0;
		while (j < wf->height)
		{
			wf->sdl->pix[i + j * wf->width] = color;
			j++;
		}
		i++;
	}
}
