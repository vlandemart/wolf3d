/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:17:55 by njacobso          #+#    #+#             */
/*   Updated: 2019/07/03 15:17:56 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		get_map(t_wf *data, int x, int y)
{
	if (x >= 0 && y >= 0 && x < data->map_size && y < data->map_size)
		return (data->map[x][y]);
	printf("%d:%d is out of bounds\n", x, y);
	return (-1);
}

/*
**	Returns hit obj value.
**	dist - distance to hit obj.
**	hit_pos - position of hit obj.
**	side - side of hit obj, value is between 0 and 3.
*/
int		raycast(t_wf *data, float angle, float *dist, t_v2 *hit_pos, int *side)
{
	t_v2	dir;
	float	step;
	int		map_obj;

	step = 0.1f;
	hit_pos->x = data->pl->posx;
	hit_pos->y = data->pl->posy;
	dir = new_v2(cos(degtorad(angle)), -sin(degtorad(angle)));
	dir.x *= step;
	dir.y *= step;
	*dist = 0;
	while (*dist < pow(data->lov, 2))
	{
		*dist += step;
		hit_pos->x += dir.x;
		hit_pos->y += dir.y;
		map_obj = get_map(data, (hit_pos->x / 64), (hit_pos->y / 64));
		if (map_obj == 1)
		{
			if ((int)(hit_pos->x - dir.x) / 64 > (int)hit_pos->x / 64)
				*side = 0;
			else if ((int)(hit_pos->x - dir.x) / 64 < (int)hit_pos->x / 64)
				*side = 1;
			else if ((int)(hit_pos->y - dir.y) / 64 > (int)hit_pos->y / 64)
				*side = 2;
			else
				*side = 3;
			return (map_obj);
		}
		if (map_obj == -1)
			return (0);
	}
	return (0);
}

void	draw_walls(t_wf *wf)
{
	int		i;
	float	dist;
	t_v2	hit;
	float	omega;
	int		side;
	int		color;

	omega = wf->pl->angle + wf->pl->fov / 2;
	if (omega >= 360)
		omega -= 360;
	i = 0;
	while (i < wf->width)
	{
		if (raycast(wf, omega, &dist, &hit, &side))
		{
			if (side == 0)
				color = 0xffffff;
			if (side == 1)
				color = 0xff0000;
			if (side == 2)
				color = 0x00ff00;
			if (side == 3)
				color = 0x0000ff;
			dist = dist * cos(degtorad(omega - wf->pl->angle));
			//fill_col(wf, i, dist, color);
			draw_wall(wf, i, dist, side + 1, side > 1 ? wf->pl->posy : wf->pl->posx);
		}
		omega -= wf->angw;
		if (omega < 0)
			omega += 360;
		i++;
	}
	update(wf, 0);
}