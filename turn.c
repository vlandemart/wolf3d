/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:20:30 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 21:22:14 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	turn_right(t_wf *wf)
{
	wf->pl->angle -= wf->pl->turn * wf->frametime;
	if (wf->pl->angle < 0)
		wf->pl->angle += 360;
}

void	turn_left(t_wf *wf)
{
	wf->pl->angle += wf->pl->turn * wf->frametime;
	if (wf->pl->angle >= 360)
		wf->pl->angle -= 360;
}
