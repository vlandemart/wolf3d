/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 23:44:02 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/29 00:22:15 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

float	find_step(float *dist)
{
	if (*dist > SQLEN * 4)
		return (6.4);
	if (*dist > SQLEN * 2)
		return (0.4);
	if (*dist < SQLEN)
		return (0.1);
	return (0.2);
}

int		find_side(int *side, t_v2 *hit_pos, t_v2 dir, int map_obj)
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

t_ray	new_ray(float angle, float dist, t_v2 hit_pos, int side)
{
	t_ray r;

	r.angle = angle;
	malloc_check(NULL, r.dist = (float*)malloc(sizeof(float)));
	*(r.dist) = dist;
	malloc_check(NULL, r.side = (int*)malloc(sizeof(int)));
	*(r.side) = side;
	malloc_check(NULL, r.hit_pos = (t_v2*)malloc(sizeof(t_v2)));
	r.hit_pos->x = hit_pos.x;
	r.hit_pos->y = hit_pos.y;
	return (r);
}

void	del_ray(t_ray *r)
{
	free(r->dist);
	free(r->side);
	free(r->hit_pos);
}
