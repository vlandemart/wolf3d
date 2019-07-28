/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:17:55 by njacobso          #+#    #+#             */
/*   Updated: 2019/07/28 19:56:43 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		get_map(t_wf *data, int x, int y)
{
	if (x >= 0 && y >= 0 && x < data->map_size && y < data->map_size)
		return (data->map[x][y]);
	//printf("%d:%d is out of bounds\n", x, y);
	return (-1);
}

void	draw_sky(t_wf *wf)
{
	float	scale;
	int i;
	int j;
	int x;
	int y;

	scale = (float)wf->height / 64.0;
	i = 0;
	while (i < (wf->height / 2) - 100)
	{
		j = 0;
		while (j < wf->width)
		{
			y = i / scale;
			x = WRAP(((int)(j / scale) - (int)(wf->pl->angle)) % 32, 32);
			float shading = wf->light_distance / (SQLEN * 4);
			wf->sdl->pix[j + i * wf->width] = rgb_multiply(get_tx(wf, TXT_SKY, x, y), shading);
			j++;
		}
		i++;
	}
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

	hit_pos->x = data->pl->pos.x;
	hit_pos->y = data->pl->pos.y;
	dir = new_v2(cos(degtorad(angle)), -sin(degtorad(angle)));
	*dist = 0;
	//step = 1;
	while (*dist < data->light_distance + SQLEN / 2)
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
		if (*dist >= data->light_distance + SQLEN / 2)
			return (0);
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

	omega = wf->pl->angle + wf->pl->fov / 2;
	if (omega >= 360)
		omega -= 360;
	i = 0;
	while (i < wf->width)
	{
		if (raycast(wf, omega, &dist, &hit, &side, 1))
		{
			dist = dist * cos(degtorad(omega - wf->pl->angle));
			draw_wall(wf, i, dist, side, side > 1 ? hit.x : hit.y);
		}
		else
		{
			wf->floor[i] = wf->height / 2;
			wf->ceil[i] = wf->height / 2;
		}
		omega -= wf->angw;
		if (omega < 0)
			omega += 360;
		i++;
	}
}

void	draw_object(t_wf *wf, t_obj obj, int x, int dist, float size)
{
	int		i;
	int		j;
	int		ex;
	int		ey;
	int		y = (wf->height - 32 * size) / 2;
	t_pix	pix;

	x -= 16 * size;
	ex = x + 32 * size;
	ey = y + 32 * size;
	i = y;
	while (i < ey && i < wf->height)
	{
		j = x;
		while (j < ex)
		{
			if (j < wf->width && j > 0)
			{
				int a = (j - x) / size;
				int b = (i - y) / size;
				pix.index = j + wf->width * i;
				pix.color = get_tx(wf, obj.tx, a, b);
				pix.dist = dist;
				pix.zbuf = 1;
				pix.wall = 1;
				put_pixel(wf, pix);
			}
			j++;
		}
		i++;
	}
}

void	draw_objects(t_wf *wf)
{
	t_list	*objs;
	t_obj	*obj;

	objs = wf->objects;
	while (objs != NULL)
	{
		obj = (t_obj*)(objs->content);

		float dx = obj->pos_real.x - wf->pl->pos.x;
		float dy = obj->pos_real.y - wf->pl->pos.y;
		float dist = sqrt(dx * dx + dy * dy);

		if (dist < wf->light_distance)
		{
			float angle = atan2(dx, dy) - degtorad(wf->pl->angle);
			if (angle < -M_PI)
				angle += 2.0 * M_PI;
			if (angle > M_PI)
				angle -= 2.0 * M_PI;
			angle -= M_PI / 2;

			if (fabs(radtodeg(angle)) <= (wf->pl->fov / 2 + 10) && obj->enabled)
			{
				int x = wf->width / 2 - tan(angle) * wf->dist;
				float size = (float)wf->dist / (cos(angle) * dist);
				draw_object(wf, *obj, x, dist, size);
			}
		}

		objs = objs->next;
	}
}
