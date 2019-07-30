/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:17:55 by njacobso          #+#    #+#             */
/*   Updated: 2019/07/30 08:38:49 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	i = -1;
	while (++i < wf->width)
	{
		wrap(r.angle, 360);
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
	}
	del_ray(&r);
}

void	draw_object(t_wf *wf, t_obj obj, t_objdraw draw)
{
	int		i;
	int		j;
	t_pix	pix;

	draw.y = (wf->height - 32 * draw.size) / 2;
	draw.x -= 16 * draw.size;
	draw.ex = draw.x + 32 * draw.size;
	draw.ey = draw.y + 32 * draw.size;
	i = draw.y;
	while (i < draw.ey && i < wf->height)
	{
		j = draw.x - 1;
		while (++j < draw.ex)
		{
			if (j < wf->width && j > 0)
			{
				draw.a = (j - draw.x) / draw.size;
				draw.b = (i - draw.y) / draw.size;
				pix = new_pix(j + wf->width * i, draw.dist, 1, 1);
				pix.color = get_tx(wf, obj.tx, draw.a, draw.b);
				put_pixel(wf, pix);
			}
		}
		i++;
	}
}

void	draw_objects(t_wf *wf)
{
	t_list	*objs;
	t_obj	*obj;
	t_v2	d;
	float	dist;

	objs = wf->objects;
	while (objs != NULL)
	{
		obj = (t_obj*)(objs->content);
		d.x = obj->pos_real.x - wf->pl->pos.x;
		d.y = obj->pos_real.y - wf->pl->pos.y;
		dist = sqrt(d.x * d.x + d.y * d.y);
		if (dist < wf->light_distance)
			check_sprite(wf, obj, get_angle(wf, d), dist);
		objs = objs->next;
	}
}
