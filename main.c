
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 15:38:52 by ydavis            #+#    #+#             */
/*   Updated: 2019/06/29 00:56:40 by ydavis           ###   ########.fr       */
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
	wf->pl->posx = 150;
	wf->pl->posy = 150;
	wf->pl->angle = 0;
	wf->pl->fov = 60;
	wf->pl->turn = 3;
	wf->pl->speed = 3;
	wf->pl->height = wf->height / 2;
	wf->lov = 4 * SQLEN;
	wf->dist = ((double)wf->width / 2.0) / tan(degtorad(wf->pl->fov) / 2.0);
	wf->angw = wf->pl->fov / wf->width;
	wf->light_distance = SQLEN * 2.5f;
}

void	init_textures(t_wf *wf)
{
	wf->tx1 = read_texture("texture_creator/brick.wolf");
	wf->tx2 = read_texture("texture_creator/wood.wolf");
	wf->tx3 = read_texture("texture_creator/stone.wolf");
	wf->tx4 = read_texture("texture_creator/box.wolf");
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
void	put_pixel(t_wf *wf, int index, int color, double dist)
{
	float shading;

	if (color == 0xff00ff)
		return;
	if (wf->zbuf[index] > dist)
		return;
	wf->zbuf[index] = dist;
	shading = 1 - (MIN(dist, wf->light_distance) / wf->light_distance);
	wf->sdl->pix[index] = rgb_multiply(color, shading);
}

void	draw_wall(t_wf *wf, int i, double dist, int check, double param)
{
	int j;
	int	height;
	int	tmp;
	int		**txt;
	double	percent;

	if (check == 1)
		txt = wf->tx1;
	else if (check == 2)
		txt = wf->tx2;
	else if (check == 3)
		txt = wf->tx3;
	else if (check == 4)
		txt = wf->tx4;
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
			put_pixel(wf, i + wf->width * j, txt[(int)param % 32][(int)(32.0 * percent)], dist);
		}
		j++;
	}
}

int	find_floor(t_wf *wf, double omega, double distfeet)
{
	double x;
	double y;
	double shading;
	int x0;
	int y0;

	omega = wf->pl->angle - omega;
	if (omega >= 360)
		omega -= 360;
	x = wf->pl->posx + (distfeet * cos(degtorad(omega)));
	y = wf->pl->posy + (distfeet * -sin(degtorad(omega)));
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
	shading = 1 - (MIN(distfeet, wf->light_distance * 0.75) / (wf->light_distance * 0.75));
	return (rgb_multiply(wf->tx2[x0][y0], shading));
}

int find_ceil(t_wf *wf, double omega, double distfeet)
{
	double x;
	double y;
	double shading;
	int x0;
	int y0;

	omega = wf->pl->angle - omega;
	if (omega >= 360)
		omega -= 360;
	x = wf->pl->posx + (distfeet * cos(degtorad(omega)));
	y = wf->pl->posy + (distfeet * -sin(degtorad(omega)));
	x0 = (int)x % (SQLEN / 2);
	y0 = (int)y % (SQLEN / 2);
	if (x0 < 0)
		x0 += SQLEN / 2;
	else if (x0 >= SQLEN / 2)
		x0 -= SQLEN / 2;
	if (y0 < 0)
		y0 += SQLEN / 2;
	else if (y0 >= SQLEN / 2)
		y0 -= SQLEN / 2;
	shading = 1 - (MIN(distfeet, wf->light_distance * 0.75) / (wf->light_distance * 0.75));
	return (rgb_multiply(wf->tx3[x0][y0], shading));
}

void	draw_ceiling(t_wf *wf)
{
	int i;
	int j;
	double distfeet;
	double omega;

	omega = -(wf->pl->fov / 2);
	i = 0;
	while (i < wf->width)
	{
		j = 0;
		while (j < wf->ceil[i])
		{
			distfeet = (wf->pl->height * wf->dist) /
				((wf->height / 2 - j) * (SQLEN / 2) * cos(degtorad(omega)));
			if (distfeet < wf->light_distance * 0.75)
				wf->sdl->pix[i + j * wf->width] = find_ceil(wf, omega, distfeet);
			j++;
		}
		i++;
		omega += wf->angw;
	}
}

void	draw_floor(t_wf *wf)
{
	int i;
	int j;
	double distfeet;
	double omega;
	
	omega = -(wf->pl->fov / 2);
	i = 0;
	while (i < wf->width)
	{
		j = wf->floor[i];
		while (j < wf->height)
		{
			distfeet = (wf->pl->height * wf->dist) /
				((j - wf->height / 2) * (SQLEN / 2) * cos(degtorad(omega)));
			if (distfeet < wf->light_distance * 0.75)
				wf->sdl->pix[i + j * wf->width] = find_floor(wf, omega, distfeet);
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
		x = wf->pl->posx;
		y = wf->pl->posy;
		x -= cos(degtorad(wf->pl->angle)) * wf->pl->speed;
		if (x < 0 || x >= wf->map_size * SQLEN || wf->map[(int)x / SQLEN][(int)y / SQLEN] == 1)
			x = wf->pl->posx;
		y += sin(degtorad(wf->pl->angle)) * wf->pl->speed;
		if (y < 0 || y >= wf->map_size * SQLEN || wf->map[(int)x / SQLEN][(int)y / SQLEN] == 1)
			y = wf->pl->posy;
		wf->pl->posx = x;
		wf->pl->posy = y;
	}

	if (wf->up)
	{
		x = wf->pl->posx;
		y = wf->pl->posy;
		x += cos(degtorad(wf->pl->angle)) * wf->pl->speed;
		if (x < 0 || x >= wf->map_size * SQLEN || wf->map[(int)x / SQLEN][(int)y / SQLEN] == 1)
			x = wf->pl->posx;
		y -= sin(degtorad(wf->pl->angle)) * wf->pl->speed;
		if (y < 0 || y >= wf->map_size * SQLEN || wf->map[(int)x / SQLEN][(int)y / SQLEN] == 1)
			y = wf->pl->posy;
		wf->pl->posx = x;
		wf->pl->posy = y;
	}

	if (wf->strafel)
	{
		x = wf->pl->posx;
		y = wf->pl->posy;
		x += cos(degtorad(wf->pl->angle + 90)) * wf->pl->speed;
		if (x < 0 || x >= wf->map_size * SQLEN || wf->map[(int)x / SQLEN][(int)y / SQLEN] == 1)
        	x = wf->pl->posx;
		y -= sin(degtorad(wf->pl->angle + 90)) * wf->pl->speed;
		if (y < 0 || y >= wf->map_size * SQLEN || wf->map[(int)x / SQLEN][(int)y / SQLEN] == 1)
			y = wf->pl->posy;
		wf->pl->posx = x;
		wf->pl->posy = y;
	}

	if (wf->strafer)
	{
		x = wf->pl->posx;
		y = wf->pl->posy;
		x += cos(degtorad(wf->pl->angle - 90)) * wf->pl->speed;
		if (x < 0 || x >= wf->map_size * SQLEN || wf->map[(int)x / SQLEN][(int)y / SQLEN] == 1)
        	x = wf->pl->posx;
		y -= sin(degtorad(wf->pl->angle - 90)) * wf->pl->speed;
		if (y < 0 || y >= wf->map_size * SQLEN || wf->map[(int)x / SQLEN][(int)y / SQLEN] == 1)
			y = wf->pl->posy;
		wf->pl->posx = x;
		wf->pl->posy = y;
	}

	if (wf->right)
	{
            wf->pl->angle -= wf->pl->turn;
            if (wf->pl->angle < 0)
                wf->pl->angle += 360;
        }

	if (wf->left)
        {
            wf->pl->angle += wf->pl->turn;
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
	    if (wf->strafel || wf->strafer || wf->down || wf->up || wf->right || wf->left)
        {
            memset(wf->sdl->pix, 0, wf->width * wf->height * sizeof(Uint32));
			//Reset z-buf
			memset(wf->zbuf, 0, wf->width * wf->height * sizeof(int));
            movement(wf);
			floor_and_ceiling(wf);
			draw_walls(wf);
			draw_floor(wf);
			draw_ceiling(wf);
			draw_objects(wf);
			update(wf, 0);
        }
		handle_events(wf);
	}
	return (0);
}
