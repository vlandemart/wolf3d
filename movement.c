/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:12:18 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 21:37:56 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	move_up(t_wf *wf)
{
	double	x;
	double	y;

	x = wf->pl->pos.x;
	y = wf->pl->pos.y;
	x += cos(degtorad(wf->pl->angle)) * wf->pl->speed * wf->frametime;
	if (!check_collision(wf, new_v2(x, y)))
		x = wf->pl->pos.x;
	y -= sin(degtorad(wf->pl->angle)) * wf->pl->speed * wf->frametime;
	if (!check_collision(wf, new_v2(x, y)))
		y = wf->pl->pos.y;
	wf->pl->pos.x = x;
	wf->pl->pos.y = y;
}

void	move_down(t_wf *wf)
{
	double	x;
	double	y;

	x = wf->pl->pos.x;
	y = wf->pl->pos.y;
	x -= cos(degtorad(wf->pl->angle)) * wf->pl->speed * wf->frametime;
	if (!check_collision(wf, new_v2(x, y)))
		x = wf->pl->pos.x;
	y += sin(degtorad(wf->pl->angle)) * wf->pl->speed * wf->frametime;
	if (!check_collision(wf, new_v2(x, y)))
		y = wf->pl->pos.y;
	wf->pl->pos.x = x;
	wf->pl->pos.y = y;
}

void	strafe_right(t_wf *wf)
{
	double	x;
	double	y;

	x = wf->pl->pos.x;
	y = wf->pl->pos.y;
	x += cos(degtorad(wf->pl->angle - 90)) * wf->pl->speed * wf->frametime;
	if (!check_collision(wf, new_v2(x, y)))
		x = wf->pl->pos.x;
	y -= sin(degtorad(wf->pl->angle - 90)) * wf->pl->speed * wf->frametime;
	if (!check_collision(wf, new_v2(x, y)))
		y = wf->pl->pos.y;
	wf->pl->pos.x = x;
	wf->pl->pos.y = y;
}

void	strafe_left(t_wf *wf)
{
	double	x;
	double	y;

	x = wf->pl->pos.x;
	y = wf->pl->pos.y;
	x += cos(degtorad(wf->pl->angle + 90)) * wf->pl->speed * wf->frametime;
	if (!check_collision(wf, new_v2(x, y)))
		x = wf->pl->pos.x;
	y -= sin(degtorad(wf->pl->angle + 90)) * wf->pl->speed * wf->frametime;
	if (!check_collision(wf, new_v2(x, y)))
		y = wf->pl->pos.y;
	wf->pl->pos.x = x;
	wf->pl->pos.y = y;
}

void	movement(t_wf *wf)
{
	if (wf->up)
		move_up(wf);
	if (wf->down)
		move_down(wf);
	if (wf->right)
		turn_right(wf);
	if (wf->left)
		turn_left(wf);
	if (wf->strafer)
		strafe_right(wf);
	if (wf->strafel)
		strafe_left(wf);
}
