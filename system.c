/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:24:21 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/30 07:59:43 by ydavis           ###   ########.fr       */
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

void	simclose(const char *str)
{
	ft_putendl(str);
	exit(1);
}

void	malloc_check(t_wf *wf, void *addr)
{
	if (!addr)
	{
		if (wf)
			exit(close_app_s(wf, "Unexpected error with malloc! Exiting..."));
		SDL_Quit();
		ft_putendl("Unexpected error with malloc! Exiting...");
		exit(1);
	}
}
