/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:23:00 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 22:08:54 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_keys(t_wf *wf, SDL_Event evt, int key)
{
	if (SDLK_LEFT == evt.key.keysym.sym)
		wf->left = key;
	if (SDLK_RIGHT == evt.key.keysym.sym)
		wf->right = key;
	if (SDLK_UP == evt.key.keysym.sym || SDLK_w == evt.key.keysym.sym)
		wf->up = key;
	if (SDLK_DOWN == evt.key.keysym.sym || SDLK_s == evt.key.keysym.sym)
		wf->down = key;
	if (SDLK_a == evt.key.keysym.sym)
		wf->strafel = key;
	if (SDLK_d == evt.key.keysym.sym)
		wf->strafer = key;
	if (SDLK_f == evt.key.keysym.sym)
		wf->fps = -wf->fps;
}

void	handle_events(t_wf *wf)
{
	SDL_Event	evt;

	while (SDL_PollEvent(&evt))
	{
		if ((SDL_QUIT == evt.type) || (SDL_KEYDOWN == evt.type &&
					SDL_SCANCODE_ESCAPE == evt.key.keysym.scancode))
			exit(close_app_s(wf, "App was closed."));
		if (SDL_KEYDOWN == evt.type)
			check_keys(wf, evt, 1);
		if (SDL_KEYUP == evt.type)
			check_keys(wf, evt, 0);
	}
}

int		cycle(t_wf *wf)
{
	wf->fps = -1;
	while (1)
	{
		wf->ftime_old = wf->ftime;
		wf->ftime = SDL_GetTicks();
		wf->time += wf->frametime;
		if (wf->flash > 0)
		{
			wf->flash -= wf->frametime;
			clamp(wf->flash, 0, 1);
		}
		if (wf->time >= 0.5)
		{
			time_update(wf);
			wf->time = 0;
		}
		calculate_frametime(wf);
		render(wf);
		handle_events(wf);
	}
	return (0);
}
