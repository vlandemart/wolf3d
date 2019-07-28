/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:24:21 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 22:09:25 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	close_app(t_wf *wf)
{
	SDL_DestroyWindow(wf->sdl->win);
	SDL_Quit();
}

int		close_app_s(t_wf *wf, char *str)
{
	ft_putendl(str);
	close_app(wf);
	return (1);
}

void	malloc_check(t_wf *wf, void *addr)
{
	if (!addr)
		exit(close_app_s(wf, "Unpredicted error with malloc! Exiting..."));
}
