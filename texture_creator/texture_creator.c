/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 19:23:12 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/29 20:53:46 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_creator.h"

t_data		*init_sdl(void)
{
	t_data	*data;

	check_malloc(data = (t_data*)malloc(sizeof(t_data)));
	SDL_Init(SDL_INIT_VIDEO);
	data->win = SDL_CreateWindow("Texture creator", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_OPENGL);
	if (!data->win)
		exit_msg(data, "SDL can't open window.");
	data->rend = SDL_CreateRenderer(data->win, -1,
		SDL_RENDERER_SOFTWARE);
	if (!data->rend)
		exit_msg(data, "SDL can't create renderer.");
	data->texture = SDL_CreateTexture(data->rend, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
	check_malloc(data->pixel = malloc(SCREEN_H * SCREEN_H * sizeof(int)));
	data->button_held = 0;
	data->pixel_size = 20;
	data->selected_color = 0xFF0000;
	data->file_name = "img";
	return (data);
}

int			set_pixel(t_data *data, int x, int y)
{
	int i;
	int j;
	int has_changed;

	has_changed = FALSE;
	i = x / data->pixel_size * data->pixel_size;
	while (i < ((x / data->pixel_size) * data->pixel_size + data->pixel_size))
	{
		j = (y / data->pixel_size) * data->pixel_size;
		while (j < ((y / data->pixel_size) *
					data->pixel_size + data->pixel_size))
		{
			if (data->pixel[SCREEN_W * j + i] != data->selected_color)
				has_changed = TRUE;
			data->pixel[SCREEN_W * j + i] = data->selected_color;
			data->image[y / data->pixel_size][x / data->pixel_size] =
				data->selected_color;
			j++;
		}
		i++;
	}
	if (has_changed == TRUE)
		txt_render(data);
	return (1);
}

int			change_color(t_data *data, int wheel)
{
	int r;
	int g;
	int b;

	r = (data->color_added == 1) ? 20 * wheel : 0;
	g = (data->color_added == 2) ? 20 * wheel : 0;
	b = (data->color_added == 3) ? 20 * wheel : 0;
	if (data->color_added == 4)
	{
		r = 10 * wheel;
		g = 10 * wheel;
		b = 10 * wheel;
	}
	clamp(wheel, -1, 1);
	data->selected_color = rgb_add(data->selected_color, r, g, b);
	rgb_split(data->selected_color, &r, &g, &b);
	ft_putstr("New color is ");
	ft_putnbr(r);
	ft_putchar(':');
	ft_putnbr(g);
	ft_putchar(':');
	ft_putnbr(b);
	ft_putchar('\n');
	return (1);
}

int			main(int ac, char **av)
{
	t_data	*data;
	char	*usage;

	data = init_sdl();
	usage = "======\nUsage:\n\
			Hold 1-3 and scroll mouse to modify rgb channels\n\
			Hold 4 and scroll mouse to darken/lighten current color\n\
			LMB presses selected color, RMB copies color under cursor\n\
			Press Space to renew image's grid\n\
			Press L or KP_Plus to export image.\n\
			Image name is set in opening argument\n\
			If image with that name exists, opens it instead\n======";
	ft_putendl(usage);
	if (ac == 2)
	{
		data->file_name = av[1];
		if (!open_file(data))
			ft_memset(data->pixel, 0x000000, SCREEN_W * SCREEN_H * sizeof(int));
	}
	else
		ft_memset(data->pixel, 0x000000, SCREEN_W * SCREEN_H * sizeof(int));
	txt_update(data);
	return (1);
}
