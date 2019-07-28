/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 15:38:52 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 19:57:59 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_map(t_wf *wf)
{
	int i;
	int j;

	wf->map = (int**)malloc(sizeof(int*) * wf->map_size);
	i = 0;
	while (i < wf->map_size)
	{
		wf->map[i] = (int*)malloc(sizeof(int) * wf->map_size);
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
	wf->map[3][4] = 1;
	wf->map[3][5] = 1;
	wf->map[4][4] = 1;
	wf->map[7][7] = 2;
}

void	init_player(t_wf *wf)
{
	wf->pl = (t_pl*)malloc(sizeof(t_pl));
	wf->pl->pos.x = 128;
	wf->pl->pos.y = 128;
	wf->pl->angle = 0;
	wf->pl->fov = 60;
	wf->pl->turn = 90;
	wf->pl->speed = 90;
	wf->pl->height = wf->height / 2;
	wf->lov = 4 * SQLEN;
	wf->dist = ((double)wf->width / 2.0) / tan(degtorad(wf->pl->fov) / 2.0);
	wf->angw = wf->pl->fov / wf->width;
	wf->light_distance = SQLEN * 2.5f;
}

void     update(t_wf *wf, int flag)
{
    if (flag)
        memset(wf->sdl->pix, 0, wf->width * wf->height * sizeof(Uint32));
    SDL_UpdateTexture(wf->sdl->txt, NULL, wf->sdl->pix, wf->width * sizeof(Uint32));
	SDL_RenderClear(wf->sdl->ren);
	SDL_RenderCopy(wf->sdl->ren, wf->sdl->txt, NULL, NULL);
	SDL_RenderPresent(wf->sdl->ren);
}

int		close_app(t_wf *wf)
{
	SDL_DestroyWindow(wf->sdl->win);
	SDL_Quit();
	return (0);
}

int		close_app_s(t_wf *wf, char *str)
{
	printf("%s\n", str);
	close_app(wf);
	return (1);
}

double	radtodeg(double rad)
{
	return (rad * (180 / M_PI));
}

double	degtorad(double deg)
{
	return (deg * (M_PI / 180));
}

//Extracted it into separate method so we have some control over
//it - we can easily add transparency, shading and z-buffer
void	put_pixel(t_wf *wf, t_pix pix)
{
	float	shading;
	int		col;

	if (pix.index < 0 || pix.index > wf->height * wf->width)
		return ;
	if (pix.color == 0xff00ff)
		return ;
	if (pix.zbuf)
	{
		if (wf->zbuf[pix.index] != 0 && wf->zbuf[pix.index] < pix.dist)
			return ;
		wf->zbuf[pix.index] = pix.dist;
	}
	col = pix.color;
	if (pix.wall)
		shading = 1 - (MIN(pix.dist, wf->light_distance) / wf->light_distance);
	else
		shading = 1 - (MIN(pix.dist, wf->light_distance * 0.75) / (wf->light_distance * 0.75));
	col = rgb_multiply(col, shading);
	if (wf->flash > 0)
		col = rgb_mix(0xffff00, col, wf->flash);
	wf->sdl->pix[pix.index] = col;
}

void	draw_wall(t_wf *wf, int i, double dist, int side, double param)
{
	int		j;
	int		height;
	int		tmp;
	double	percent;
	t_pix	pix;

	height = SQLEN * wf->dist / dist / 2;
	tmp = (wf->height - height) / 2;
	wf->floor[i] = tmp + height;
	wf->ceil[i] = tmp;
	j = 0;
	while (j < wf->height)
	{
		if (j > tmp && j < tmp + height)
		{
			percent = (double)(j - tmp) / (double)height;
			pix.index = i + wf->width * j;
			pix.color = get_tx(wf, side, (int)param % 32, (int)(32.0 * percent));
			pix.dist = dist;
			pix.zbuf = 1;
			pix.wall = 1;
			put_pixel(wf, pix);
			//put_pixel(wf, i + wf->width * j, get_tx(wf, side, (int)param % 32, (int)(32.0 * percent)), dist, 1);
		}
		j++;
	}
}

int	find_floor(t_wf *wf, double omega, double distfeet)
{
	double x;
	double y;
	int x0;
	int y0;

	omega = wf->pl->angle - omega;
	if (omega >= 360)
		omega -= 360;
	x = wf->pl->pos.x + (distfeet * cos(degtorad(omega)));
	y = wf->pl->pos.y + (distfeet * -sin(degtorad(omega)));
	x0 = (int)x % (SQLEN / 2);
	y0 = (int)y % (SQLEN / 2);
	if (x0 < 0)
		x0 += SQLEN / 2;
	else if (x0 >= SQLEN / 2)
		x0 -= SQLEN / 2;
	if (y0 >= SQLEN / 2)
		y0 -= SQLEN / 2;
	else if (y0 < 0)
		y0 += SQLEN / 2;
	return (get_tx(wf, TXT_WOOD, x0, y0));
}

int find_ceil(t_wf *wf, double omega, double distfeet)
{
	double x;
	double y;
	int x0;
	int y0;

	omega = wf->pl->angle - omega;
	if (omega >= 360)
		omega -= 360;
	x = wf->pl->pos.x + (distfeet * cos(degtorad(omega)));
	y = wf->pl->pos.y + (distfeet * -sin(degtorad(omega)));
	x0 = (int)x % (SQLEN / 2);
	y0 = (int)y % (SQLEN / 2);
	if (x0 < 0)
		x0 += SQLEN / 2;
	else if (x0 >= SQLEN / 2)
		x0 -= SQLEN / 2;
	if (y0 >= SQLEN / 2)
		y0 -= SQLEN / 2;
	else if (y0 < 0)
		y0 += SQLEN / 2;
	return (get_tx(wf, TXT_STONE, x0, y0));
}

void	draw_ceiling(t_wf *wf)
{
	int		i;
	int		j;
	double	distfeet;
	double	omega;
	t_pix	pix;

	omega = -(wf->pl->fov / 2);
	i = 0;
	while (i < wf->width)
	{
		j = 0;
		while (j < wf->ceil[i])
		{
			if (wf->zbuf[i + j * wf->width] == 0)
			{
				distfeet = (wf->pl->height * wf->dist) /
					((wf->height / 2 - j) * (SQLEN / 2) * cos(degtorad(omega)));
				if (distfeet < wf->light_distance * 0.75)
				{		
					pix.index = i + wf->width * j;
					pix.color = find_ceil(wf, omega, distfeet);
					pix.dist = distfeet;
					pix.zbuf = 0;
					pix.wall = 0;
					put_pixel(wf, pix);
				}
			}
			j++;
		}
		i++;
		omega += wf->angw;
	}
}

void	draw_floor(t_wf *wf)
{
	int		i;
	int		j;
	double	distfeet;
	double	omega;
	t_pix	pix;
	
	omega = -(wf->pl->fov / 2);
	i = 0;
	while (i < wf->width)
	{
		j = wf->floor[i];
		while (j < wf->height)
		{
			if (wf->zbuf[i + j * wf->width] == 0)
			{
				distfeet = (wf->pl->height * wf->dist) /
					((j - wf->height / 2) * (SQLEN / 2) * cos(degtorad(omega)));
				if (distfeet < wf->light_distance)
				{
					pix.index = i + wf->width * j;
					pix.color = find_floor(wf, omega, distfeet);
					pix.dist = distfeet;
					pix.zbuf = 0;
					pix.wall = 0;
					put_pixel(wf, pix);
				}
			}
			j++;
		}
		i++;
		omega += wf->angw;
	}
}

void	prepare_window(t_wf *wf)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	wf->sdl->win = SDL_CreateWindow("HEY THERE", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, wf->width, wf->height, 0);
	wf->sdl->ren = SDL_CreateRenderer(wf->sdl->win, -1, 0);
	wf->sdl->txt = SDL_CreateTexture(wf->sdl->ren,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, wf->width, wf->height);
	wf->sdl->pix = (Uint32*)malloc(sizeof(Uint32) * (wf->width * wf->height));
	update(wf, 1);
}

void movement(t_wf *wf)
{
	double x;
	double y;

	if (wf->down)
	{
		x = wf->pl->pos.x;
		y = wf->pl->pos.y;
		x -= cos(degtorad(wf->pl->angle)) * wf->pl->speed * wf->frametime;
		
		if (check_collision(wf, new_v2(x, y)) == 0)
			x = wf->pl->pos.x;
		y += sin(degtorad(wf->pl->angle)) * wf->pl->speed * wf->frametime;
		if (check_collision(wf, new_v2(x, y)) == 0)
			y = wf->pl->pos.y;
		wf->pl->pos.x = x;
		wf->pl->pos.y = y;
	}

	if (wf->up)
	{
		x = wf->pl->pos.x;
		y = wf->pl->pos.y;
		x += cos(degtorad(wf->pl->angle)) * wf->pl->speed * wf->frametime;
		if (check_collision(wf, new_v2(x, y)) == 0)
			x = wf->pl->pos.x;
		y -= sin(degtorad(wf->pl->angle)) * wf->pl->speed * wf->frametime;
		if (check_collision(wf, new_v2(x, y)) == 0)
			y = wf->pl->pos.y;
		wf->pl->pos.x = x;
		wf->pl->pos.y = y;
	}

	if (wf->strafel)
	{
		x = wf->pl->pos.x;
		y = wf->pl->pos.y;
		x += cos(degtorad(wf->pl->angle + 90)) * wf->pl->speed * wf->frametime;
		if (check_collision(wf, new_v2(x, y)) == 0)
			x = wf->pl->pos.x;
		y -= sin(degtorad(wf->pl->angle + 90)) * wf->pl->speed * wf->frametime;
		if (check_collision(wf, new_v2(x, y)) == 0)
			y = wf->pl->pos.y;
		wf->pl->pos.x = x;
		wf->pl->pos.y = y;
	}

	if (wf->strafer)
	{
		x = wf->pl->pos.x;
		y = wf->pl->pos.y;
		x += cos(degtorad(wf->pl->angle - 90)) * wf->pl->speed * wf->frametime;
		if (check_collision(wf, new_v2(x, y)) == 0)
			x = wf->pl->pos.x;
		y -= sin(degtorad(wf->pl->angle - 90)) * wf->pl->speed * wf->frametime;
		if (check_collision(wf, new_v2(x, y)) == 0)
			y = wf->pl->pos.y;
		wf->pl->pos.x = x;
		wf->pl->pos.y = y;
	}

	if (wf->right)
	{
            wf->pl->angle -= wf->pl->turn * wf->frametime;
            if (wf->pl->angle < 0)
                wf->pl->angle += 360;
        }

	if (wf->left)
        {
            wf->pl->angle += wf->pl->turn * wf->frametime;
            if (wf->pl->angle >= 360)
                wf->pl->angle -= 360;
        }
}

void	floor_and_ceiling(t_wf *data)
{
	int i;
	int j;
	int color;

	color = 0;
	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			data->sdl->pix[i * data->width + j] = color;
			j++;
		}
		i++;
	}
}

void	handle_events(t_wf *wf)
{
	SDL_Event	evt;

	while (SDL_PollEvent(&evt))
	{
		if ((SDL_QUIT == evt.type) ||
				(SDL_KEYDOWN == evt.type &&
					SDL_SCANCODE_ESCAPE == evt.key.keysym.scancode))
			exit(close_app_s(wf, "App was closed."));
		if (SDL_KEYDOWN == evt.type)
		{
			if (SDLK_LEFT == evt.key.keysym.sym)
				wf->left = 1;
			if (SDLK_RIGHT == evt.key.keysym.sym)
				wf->right = 1;
			if (SDLK_UP == evt.key.keysym.sym || SDLK_w == evt.key.keysym.sym)
				wf->up = 1;
			if (SDLK_DOWN == evt.key.keysym.sym || SDLK_s == evt.key.keysym.sym)
				wf->down = 1;
			if (SDLK_a == evt.key.keysym.sym)
				wf->strafel = 1;
			if (SDLK_d == evt.key.keysym.sym)
				wf->strafer = 1;
		}
		if (SDL_KEYUP == evt.type)
		{
			if (SDLK_LEFT == evt.key.keysym.sym)
				wf->left = 0;
			if (SDLK_RIGHT == evt.key.keysym.sym)
				wf->right = 0;
			if (SDLK_UP == evt.key.keysym.sym || SDLK_w == evt.key.keysym.sym)
				wf->up = 0;
			if (SDLK_DOWN == evt.key.keysym.sym || SDLK_s == evt.key.keysym.sym)
				wf->down = 0;
			if (SDLK_a == evt.key.keysym.sym)
				wf->strafel = 0;
			if (SDLK_d == evt.key.keysym.sym)
				wf->strafer = 0;
		}
	}
}

void	calculate_frametime(t_wf *wf)
{
	wf->frametime = (float)(wf->ftime - wf->ftime_old) / (float)1000;
	printf("FPS: %f\n", 1 / wf->frametime);
}

void	time_update(t_wf *wf)
{
	wf->anim_frame++;
	if (wf->anim_frame > 1)
		wf->anim_frame = 0;
	if (RAN(0, 10) > 9)
		wf->light_distance += SQLEN;
}

void	render(t_wf *wf)
{
	memset(wf->sdl->pix, 0, wf->width * wf->height * sizeof(Uint32));
	memset(wf->zbuf, 0, wf->width * wf->height * sizeof(int));
	movement(wf);
	//floor_and_ceiling(wf);
	draw_sky(wf);
	draw_walls(wf);
	draw_floor(wf);
	//draw_ceiling(wf);
	draw_objects(wf);
	update(wf, 0);
}

int main(int ac, char **av)
{
	t_wf		*wf;

	wf = (t_wf*)malloc(sizeof(t_wf));
	wf->width = 1024;
	wf->height = 768;
	wf->left = 0;
	wf->right = 0;
	wf->up = 0;
	wf->down = 0;
	wf->strafer = 0;
	wf->strafel = 0;

	if (ac == 2)
	{
		if (read_map(wf, av[1]) != 1)
			exit(close_app_s(wf, "Error reading map!"));
	}
	else
	{
		printf("No map passed, initing empty room.\n");
		wf->map_size = 10;
		init_map(wf);
	}

	wf->zbuf = malloc(sizeof(int) * wf->width * wf->height);

	init_player(wf);

	init_textures(wf);

	wf->floor = (int*)malloc(sizeof(int) * wf->width);
	wf->ceil = (int*)malloc(sizeof(int) * wf->width);

	wf->sdl = (t_sdl*)malloc(sizeof(t_sdl));
	prepare_window(wf);

	floor_and_ceiling(wf);
	draw_walls(wf);
	draw_floor(wf);
	draw_ceiling(wf);
	update(wf, 0);

	while (1)
	{
		wf->ftime_old = wf->ftime;
		wf->ftime = SDL_GetTicks();
		wf->time += wf->frametime;
		if (wf->flash > 0)
		{
			wf->flash -= wf->frametime;
			CLAMP(wf->flash, 0, 1);
		}
		if (wf->time >= 0.5)
		{
			time_update(wf);
			wf->time = 0;
		}
		if (wf->light_distance > SQLEN * 2.5f)
			wf->light_distance -= SQLEN * wf->frametime;
		//if (wf->strafel || wf->strafer || wf->down || wf->up || wf->right || wf->left)
		calculate_frametime(wf);
		render(wf);
		handle_events(wf);
	}
	return (0);
}
