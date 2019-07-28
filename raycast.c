/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:17:55 by njacobso          #+#    #+#             */
/*   Updated: 2019/07/29 00:28:39 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		get_map(t_wf *data, int x, int y)
{
	if (x >= 0 && y >= 0 && x < data->map_size && y < data->map_size)
		return (data->map[x][y]);
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putnbr(y);
	ft_putendl(" is out of bounds");
	return (-1);
}

void	draw_sky(t_wf *wf)
{
	float	scale;
	int		i;
	int		j;
	int		x;
	int		y;

	scale = (float)wf->height / 64.0;
	i = 0;
	while (i < (wf->height / 2) - 100)
	{
		j = 0;
		while (j < wf->width)
		{
			y = i / scale;
			x = (int)wrap(((int)(j / scale) - (int)(wf->pl->angle)) % 32, 32);
			wf->sdl->pix[j + i * wf->width] = rgb_multiply(get_tx(wf,
						TXT_SKY, x, y), wf->light_distance / (SQLEN * 4));
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

int		raycast(t_wf *data, t_ray *r, int mask)
{
	t_v2	dir;
	float	step;
	int		map_obj;

	r->hit_pos->x = data->pl->pos.x;
	r->hit_pos->y = data->pl->pos.y;
	dir = new_v2(cos(degtorad(r->angle)), -sin(degtorad(r->angle)));
	*(r->dist) = 0;
	while (*(r->dist) < data->light_distance + SQLEN / 2)
	{
		step = find_step(r->dist);
		*(r->dist) += step;
		if (*(r->dist) >= data->light_distance + SQLEN / 2)
			return (0);
		r->hit_pos->x += dir.x * step;
		r->hit_pos->y += dir.y * step;
		map_obj = get_map(data, (r->hit_pos->x / SQLEN),
				(r->hit_pos->y / SQLEN));
		if (map_obj == mask || (map_obj && map_obj != 1 && mask == 0))
			return (find_side(r->side, r->hit_pos, dir, map_obj));
		if (map_obj == -1)
			return (0);
	}
	return (0);
}

void	draw_walls(t_wf *wf)
{
	int		i;
	t_ray	r;

	r = new_ray(wf->pl->angle + wf->pl->fov / 2, 0, new_v2(0, 0), 0);
	if (r.angle >= 360)
		r.angle -= 360;
	i = -1;
	while (++i < wf->width)
	{
		if (raycast(wf, &r, 1))
		{
			*(r.dist) = *(r.dist) * cos(degtorad(r.angle - wf->pl->angle));
			draw_wall(wf, new_wall(i, *(r.dist), *(r.side), *(r.side) > 1 ?
						r.hit_pos->x : r.hit_pos->y));
		}
		else
		{
			wf->floor[i] = wf->height / 2;
			wf->ceil[i] = wf->height / 2;
		}
		r.angle -= wf->angw;
		if (r.angle < 0)
			r.angle += 360;
	}
	del_ray(&r);
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
				pix = new_pix(j + wf->width * i, dist, 1, 1);
				pix.color = get_tx(wf, obj.tx, a, b);
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
