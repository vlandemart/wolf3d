/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 20:09:35 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/29 20:29:36 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_creator.h"

void	check_mousebutton(t_data *data, SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
			data->button_held = TRUE;
		else
			pick_color(data, event.motion.x, event.motion.y);
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
		data->button_held = FALSE;
	else if (event.type == SDL_MOUSEMOTION && data->button_held)
		set_pixel(data, event.motion.x, event.motion.y);
}

void	check_keypress(t_data *data, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_SPACE)
		draw_grid(data);
	else if (event.key.keysym.sym == SDLK_1)
		data->color_added = 1;
	else if (event.key.keysym.sym == SDLK_2)
		data->color_added = 2;
	else if (event.key.keysym.sym == SDLK_3)
		data->color_added = 3;
	else if (event.key.keysym.sym == SDLK_4)
		data->color_added = 4;
	else if (event.key.keysym.sym == SDLK_l ||
			event.key.keysym.sym == SDLK_KP_PLUS)
		export_image(data);
}

void	check_keyrelease(t_data *data, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_1 ||
			event.key.keysym.sym == SDLK_2 ||
			event.key.keysym.sym == SDLK_3)
		data->color_added = 0;
}

int		event_handle(t_data *data)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || (SDL_KEYDOWN == event.type &&
					SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
			exit_msg(data, "App was closed.");
		else if (event.type == SDL_MOUSEBUTTONDOWN ||
				event.type == SDL_MOUSEBUTTONUP ||
				(event.type == SDL_MOUSEMOTION && data->button_held))
			check_mousebutton(data, event);
		else if (event.type == SDL_KEYDOWN)
			check_keypress(data, event);
		else if (event.type == SDL_KEYUP)
			check_keyrelease(data, event);
		if (event.type == SDL_MOUSEWHEEL)
			change_color(data, event.wheel.y);
	}
	return (0);
}

int		exit_msg(t_data *data, char *die_msg)
{
	SDL_DestroyWindow(data->win);
	SDL_Quit();
	ft_putendl(die_msg);
	exit(1);
}
