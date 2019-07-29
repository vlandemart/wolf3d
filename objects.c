/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 18:55:12 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/29 19:19:57 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		check_sprite(t_wf *wf, t_obj *obj, float angle, float dist)
{
	int		x;
	float	size;

	if (fabs(radtodeg(angle)) <= (wf->pl->fov / 2 + 10) && obj->enabled)
	{
		x = wf->width / 2 - tan(angle) * wf->dist;
		size = (float)wf->dist / (cos(angle) * dist);
		draw_object(wf, *obj, new_objdraw(x, dist, size));
	}
}

float		get_angle(t_wf *wf, t_v2 d)
{
	float	angle;

	angle = atan2(d.x, d.y) - degtorad(wf->pl->angle);
	if (angle < -M_PI)
		angle += 2.0 * M_PI;
	if (angle > M_PI)
		angle -= 2.0 * M_PI;
	angle -= M_PI / 2;
	return (angle);
}

t_objdraw	new_objdraw(int x, int dist, float size)
{
	t_objdraw	obj;

	obj.x = x;
	obj.dist = dist;
	obj.size = size;
	return (obj);
}
