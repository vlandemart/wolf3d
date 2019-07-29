/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorceil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:51:26 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/29 19:19:04 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		floor_ceil(t_wf *wf, double omega, double distfeet, int txt)
{
	double	x;
	double	y;
	int		x0;
	int		y0;

	omega = wf->pl->angle - omega;
	if (omega >= 360)
		omega -= 360;
	x = wf->pl->pos.x + (distfeet * cos(degtorad(omega)));
	y = wf->pl->pos.y + (distfeet * -sin(degtorad(omega)));
	x0 = (int)x % (SQLEN / 2);
	y0 = (int)y % (SQLEN / 2);
	if (x0 < 0)
		x0 += SQLEN / 2;
	else if (x0 >= SQLEN / 2)
		x0 -= SQLEN / 2;
	if (y0 < 0)
		y0 += SQLEN / 2;
	else if (y0 >= SQLEN / 2)
		y0 -= SQLEN / 2;
	return (get_tx(wf, txt, x0, y0));
}

void	check_ceiling(t_wf *wf, int i, int j, double omega)
{
	double	distfeet;
	t_pix	pix;

	if (wf->zbuf[i + j * wf->width] == 0)
	{
		distfeet = wf->pl->height * wf->dist /
			((wf->height / 2 - j) * (SQLEN / 2) * cos(degtorad(omega)));
		if (distfeet < wf->light_distance * 0.75)
		{
			pix = new_pix(i + j * wf->width, distfeet, 0, 0);
			pix.color = floor_ceil(wf, omega, distfeet, TXT_STONE);
			put_pixel(wf, pix);
		}
	}
}

void	check_floor(t_wf *wf, int i, int j, double omega)
{
	double	distfeet;
	t_pix	pix;

	if (wf->zbuf[i + j * wf->width] == 0)
	{
		distfeet = (wf->pl->height * wf->dist) /
			((j - wf->height / 2) * (SQLEN / 2) * cos(degtorad(omega)));
		if (distfeet < wf->light_distance)
		{
			pix = new_pix(i + j * wf->width, distfeet, 0, 0);
			pix.color = floor_ceil(wf, omega, distfeet, TXT_FLOOR);
			put_pixel(wf, pix);
		}
	}
}

void	draw_ceilfloor(t_wf *wf)
{
	int		i;
	int		j;
	double	omega;

	omega = -(wf->pl->fov / 2);
	i = 0;
	while (i < wf->width)
	{
		j = wf->floor[i];
		while (j < wf->height)
		{
			check_floor(wf, i, j, omega);
			j++;
		}
		i++;
		omega += wf->angw;
	}
}

void	init_floorceil(t_wf *wf)
{
	malloc_check(wf, wf->floor = (int*)malloc(sizeof(int) * wf->width));
	malloc_check(wf, wf->ceil = (int*)malloc(sizeof(int) * wf->width));
}
