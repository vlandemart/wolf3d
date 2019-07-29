/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 19:34:05 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/29 21:07:21 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_creator.h"

int		txt_render(t_data *data)
{
	SDL_UpdateTexture(data->texture, NULL, data->pixel, SCREEN_W * 4);
	SDL_RenderClear(data->rend);
	SDL_RenderCopy(data->rend, data->texture, NULL, NULL);
	SDL_RenderPresent(data->rend);
	return (1);
}

int		txt_update(t_data *data)
{
	while (TRUE)
	{
		event_handle(data);
		txt_render(data);
	}
	return (1);
}

void	check_malloc(void *addr)
{
	if (!addr)
	{
		SDL_Quit();
		ft_putendl("Unexpected error with malloc.");
		exit(1);
	}
}
