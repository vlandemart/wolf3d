/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 19:35:24 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 22:36:51 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

float	distance(t_v2 pos1, t_v2 pos2)
{
	float dx;
	float dy;
	float dist;

	dx = pos1.x - pos2.x;
	dy = pos1.y - pos2.y;
	dist = sqrt(dx * dx + dy * dy);
	return (clamp(dist, 1, 999));
}

/*
**	Return values are:
**	1 if has collision
**	0 if no collision
*/

int		check_collision(t_wf *wf, t_v2 pos)
{
	t_list	*objs;
	t_obj	*obj;

	if (pos.x < 0 || pos.y < 0 || pos.x > wf->map_size * SQLEN ||
			pos.y > wf->map_size * SQLEN)
		return (0);
	if (wf->map[(int)pos.x / SQLEN][(int)pos.y / SQLEN] == 1)
		return (0);
	objs = wf->objects;
	while (objs != NULL)
	{
		obj = (t_obj*)(objs->content);
		if (obj->enabled && distance(obj->pos_real, pos) <= 24)
		{
			if (obj->on_col != NULL)
				obj->on_col(wf, obj);
			return (obj->passable);
		}
		objs = objs->next;
	}
	return (1);
}
