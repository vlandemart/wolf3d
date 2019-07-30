/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:10:55 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/30 08:11:33 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_map(t_wf *wf)
{
	int i;
	int j;

	malloc_check(wf, wf->map = (int**)malloc(sizeof(int*) * wf->map_size));
	i = 0;
	while (i < wf->map_size)
	{
		malloc_check(wf, wf->map[i] = (int*)malloc(sizeof(int) * wf->map_size));
		j = 0;
		while (j < wf->map_size)
		{
			if (!i || !j || i == wf->map_size - 1 || j == wf->map_size - 1)
				wf->map[i][j] = 1;
			else
				wf->map[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	init_player(t_wf *wf)
{
	malloc_check(wf, wf->pl = (t_pl*)malloc(sizeof(t_pl)));
	player_find(wf);
	wf->pl->angle = 0;
	wf->pl->fov = 60;
	wf->pl->turn = 90;
	wf->pl->speed = 90;
	wf->pl->speed = 90;
	wf->pl->height = wf->height / 2;
	wf->lov = 4 * SQLEN;
	wf->dist = ((double)wf->width / 2.0) / tan(degtorad(wf->pl->fov) / 2.0);
	wf->angw = wf->pl->fov / wf->width;
	wf->light_distance = SQLEN * 2.5;
}

void	init_const(t_wf *wf)
{
	wf->width = 1024;
	wf->height = 768;
	wf->left = 0;
	wf->right = 0;
	wf->up = 0;
	wf->down = 0;
	wf->strafel = 0;
	wf->strafer = 0;
	wf->m = 1;
}

void	prepare_window(t_wf *wf)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		simclose(SDL_GetError());
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
		simclose(SDL_GetError());
	if (!(wf->music = Mix_LoadMUS("music.mp3")))
		simclose(SDL_GetError());
	if (!(wf->sdl->win = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, wf->width, wf->height, 0)))
		simclose(SDL_GetError());
	if (!(wf->sdl->ren = SDL_CreateRenderer(wf->sdl->win, -1, 0)))
		simclose(SDL_GetError());
	if (!(wf->sdl->txt = SDL_CreateTexture(wf->sdl->ren,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
			wf->width, wf->height)))
		simclose(SDL_GetError());
	malloc_check(wf, wf->sdl->pix = (Uint32*)malloc(sizeof(Uint32) *
				(wf->width * wf->height)));
	update(wf, 1);
}

t_wf	*init_wf(int ac, char **av)
{
	t_wf *wf;

	malloc_check(NULL, wf = (t_wf*)malloc(sizeof(t_wf)));
	init_const(wf);
	init_args(wf, ac, av);
	malloc_check(wf, wf->zbuf = malloc(sizeof(int) * wf->width * wf->height));
	init_player(wf);
	init_textures(wf);
	init_floorceil(wf);
	malloc_check(wf, wf->sdl = (t_sdl*)malloc(sizeof(t_sdl)));
	prepare_window(wf);
	floor_and_ceiling(wf);
	draw_walls(wf);
	draw_ceilfloor(wf);
	update(wf, 0);
	return (wf);
}
