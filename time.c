/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:32:53 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 22:19:38 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	calculate_frametime(t_wf *wf)
{
	wf->frametime = (float)(wf->ftime - wf->ftime_old) / (float)1000;
	ft_putstr("FPS: ");
	ft_putnbr((int)1 / wf->frametime);
	ft_putchar('\n');
}

void	time_update(t_wf *wf)
{
	wf->anim_frame++;
	if (wf->anim_frame > 1)
		wf->anim_frame = 0;
}
