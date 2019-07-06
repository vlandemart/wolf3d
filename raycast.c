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
int		raycast(t_wf *data, float angle, float *dist, t_v2 *hit_pos, int *side, int mask)
{
	t_v2	dir;
	float	step;
	int		map_obj;

	hit_pos->x = data->pl->posx;
	hit_pos->y = data->pl->posy;
	dir = new_v2(cos(degtorad(angle)), -sin(degtorad(angle)));
	*dist = 0;
	while (*dist < SQLEN * 8)
	{
		if (*dist > SQLEN * 4)
			step = 6.4f;
		else if (*dist > SQLEN * 2)
			step = .4f;
		else if (*dist < SQLEN)
			step = 0.1f;
		else
			step = 0.2f;
		*dist += step;
		hit_pos->x += dir.x * step;
		hit_pos->y += dir.y * step;
		map_obj = get_map(data, (hit_pos->x / SQLEN), (hit_pos->y / SQLEN));
		if (map_obj == mask || (map_obj && map_obj != 1 && mask == 0))
		{
			if ((int)(hit_pos->x - dir.x) / SQLEN > (int)hit_pos->x / SQLEN)
				*side = 0;
			else if ((int)(hit_pos->x - dir.x) / SQLEN < (int)hit_pos->x / SQLEN)
				*side = 1;
			else if ((int)(hit_pos->y - dir.y) / SQLEN > (int)hit_pos->y / SQLEN)
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
		if (raycast(wf, omega, &dist, &hit, &side, 1))
		{
			dist = dist * cos(degtorad(omega - wf->pl->angle));
			draw_wall(wf, i, dist, side + 1, side > 1 ? hit.x : hit.y);
		}
		omega -= wf->angw;
		if (omega < 0)
			omega += 360;
		i++;
	}
	update(wf, 0);
}