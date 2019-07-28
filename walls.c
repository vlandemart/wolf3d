/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:39:09 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 20:48:56 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_wall	new_wall(int i, double dist, int side, double param)
{
	t_wall wall;

	wall.i = i;
	wall.dist = dist;
	wall.side = side;
	wall.param = param;
	return (wall);
}

t_pix	new_pix(int index, double dist, int zbuf, int wall)
{
	t_pix pix;

	pix.dist = dist;
	pix.zbuf = zbuf;
	pix.wall = wall;
	pix.index = index;
	return (pix);
}

void	draw_wall(t_wf *wf, t_wall wall)
{
	int		j;
	int		height;
	int		tmp;
	double	percent;
	t_pix	pix;

	height = SQLEN * wf->dist / wall.dist / 2;
	tmp = (wf->height - height) / 2;
	wf->floor[wall.i] = tmp + height;
	wf->ceil[wall.i] = tmp;
	j = 0;
	while (j < wf->height)
	{
		if (j > tmp && j < tmp + height)
		{
			percent = (double)(j - tmp) / (double)height;
			pix = new_pix(wall.i + wf->width * j, wall.dist, 1, 1);
			pix.color = get_tx(wf, wall.side, (int)(wall.param) % 32,
					(int)(32.0 * percent));
			put_pixel(wf, pix);
		}
		j++;
	}
}
