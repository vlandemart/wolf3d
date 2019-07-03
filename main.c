
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
}

void	init_player(t_wf *wf)
{
	wf->pl = (t_pl*)malloc(sizeof(t_pl));
	wf->pl->posx = 127;
	wf->pl->posy = 127;
	wf->pl->angle = 45;
	wf->pl->fov = 60;
	wf->pl->turn = 1;
	wf->pl->speed = 1;
	wf->lov = 4 * 64;
	wf->dist = ((double)wf->width / 2.0) / tan(degtorad(wf->pl->fov) / 2.0);
	wf->angw = wf->pl->fov / wf->width;
	wf->light_distance = 150.0f;
}

void	init_tx1(t_wf *wf)
{
	int i;
	int j;

	i = 0;
	wf->tx1 = (int**)malloc(sizeof(int*) * 64);
	while (i < 64)
	{
		wf->tx1[i] = (int*)malloc(sizeof(int) * 64);
		j = 0;
		while (j < 64)
		{
			if (i && j && i != 63 && j != 63)
				wf->tx1[i][j] = 0x0000ff;
			else
				wf->tx1[i][j] = 0xffffff;
			j++;
		}
		i++;
	}
	wf->tx1[32][32] = 0xffffff;
}

void	init_tx2(t_wf *wf)
{
	int i;
	int j;

	i = 0;
	wf->tx2 = (int**)malloc(sizeof(int*) * 64);
	while (i < 64)
	{
		wf->tx2[i] = (int*)malloc(sizeof(int) * 64);
		j = 0;
		while (j < 64)
		{
			if (i && j && i != 63 && j != 63)
				wf->tx2[i][j] = 0x00ff00;
			else
				wf->tx2[i][j] = 0xffffff;
			j++;
		}
		i++;
	}
	wf->tx2[32][32] = 0xffffff;
}

void	init_tx3(t_wf *wf)
{
	int i;
	int j;

	i = 0;
	wf->tx3 = (int**)malloc(sizeof(int*) * 64);
	while (i < 64)
	{
		wf->tx3[i] = (int*)malloc(sizeof(int) * 64);
		j = 0;
		while (j < 64)
		{
			if (i && j && i != 63 && j != 63)
				wf->tx3[i][j] = 0x00ffff;
			else
				wf->tx3[i][j] = 0xffffff;
			j++;
		}
		i++;
	}
	wf->tx3[32][32] = 0xffffff;
}

void	init_tx4(t_wf *wf)
{
	int i;
	int j;

	i = 0;
	wf->tx4 = (int**)malloc(sizeof(int*) * 64);
	while (i < 64)
	{
		wf->tx4[i] = (int*)malloc(sizeof(int) * 64);
		j = 0;
		while (j < 64)
		{
			if (i  && j && i != 63 && j != 63)
				wf->tx4[i][j] = 0xff0000;
			else
				wf->tx4[i][j] = 0xffffff;
			j++;
		}
		i++;
	}
	wf->tx4[32][32] = 0xffffff;
}

void	init_textures(t_wf *wf)
{
	init_tx1(wf);
	init_tx2(wf);
	init_tx3(wf);
	init_tx4(wf);
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

double	degtorad(double deg)
{
	return (deg * (M_PI / 180));
}

void	fill_col(t_wf *wf, int i, double dist, int check, double param)
{
	int j;
	int	height;
	int	tmp;
	int		**txt;
	float shading;
	double	percent;

	if (check == 1)
		txt = wf->tx1;
	else if (check == 2)
		txt = wf->tx2;
	else if (check == 3)
		txt = wf->tx3;
	else if (check == 4)
		txt = wf->tx4;
	shading = 1 - (MIN(dist, wf->light_distance) / wf->light_distance);
	height = SQLEN * wf->dist / dist / 2;
	tmp = (wf->height - height) / 2;
	j = 0;
	while (j < wf->height)
	{
		if (j > tmp && j < tmp + height)
		{
			percent = (double)(j - tmp) / (double)height;
			wf->sdl->pix[i + wf->width * j] = rgb_multiply(txt[(int)param % 64][(int)(64.0 * percent)], shading);
		}
		j++;
	}
}

void	test(t_wf *wf)
{
    int i;
    int check;
    double x;
    double y;
    double distx;
    double disty;
    double omega;
    double xmove;
    double ymove;
    double dist;
    double tmp;
	double	send;
    int col;

    omega = wf->pl->angle + wf->pl->fov / 2;
    if (omega >= 360)
        omega -= 360;
    i = 0;
    tmp = pow(wf->lov, 2);
    while (i < wf->width)
	{
		check = 0;
        x = wf->pl->posx;
        y = wf->pl->posy;
    	col = 0;
        xmove = cos(degtorad(omega));
        ymove = -sin(degtorad(omega));
        distx = 0.0;
        disty = 0.0;
        while (x >= 0 && y >= 0 && x < wf->map_size * 64 &&
				y < wf->map_size * 64 &&
				pow(distx, 2) + pow(disty, 2) < tmp)
        {
            if (wf->map[(int)(x / 64)][(int)(y / 64)])
            {
                if ((int)(x - xmove) / 64 > (int)x / 64)
				{
					send = y;
					check = 1;
				}
				else if ((int)(x - xmove) / 64 < (int)x / 64)
				{
					send = y;
					check = 2;
				}
				else if ((int)(y - ymove) / 64 > (int)y / 64)
				{
					send = x;
					check = 3;
                }
				else
				{
					send = x;
					check = 4;
				}
				break ;
            }
            x += xmove;
            y += ymove;
            distx += xmove;
            disty += ymove;
        }
        dist = sqrt(pow(distx, 2) + pow(disty, 2));
       	dist = fabs(dist * fabs(cos(degtorad(omega - wf->pl->angle))));
	if (check)
        	fill_col(wf, i, dist, check, send);
	omega -= wf->angw;
	    if (omega < 0)
            omega += 360;
		i++;
	}

	update(wf, 0);
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
            if (x < 0 || x >= wf->map_size * 64 || wf->map[(int)x / 64][(int)y / 64])
                x = wf->pl->posx;
            y += sin(degtorad(wf->pl->angle)) * wf->pl->speed;
            if (y < 0 || y >= wf->map_size * 64 || wf->map[(int)x / 64][(int)y / 64])
                y = wf->pl->posy;
            wf->pl->posx = x;
            wf->pl->posy = y;
        }

	if (wf->up)
        {
            x = wf->pl->posx;
            y = wf->pl->posy;
            x += cos(degtorad(wf->pl->angle)) * wf->pl->speed;
            if (x < 0 || x >= wf->map_size * 64 || wf->map[(int)x / 64][(int)y / 64])
                x = wf->pl->posx;
            y -= sin(degtorad(wf->pl->angle)) * wf->pl->speed;
            if (y < 0 || y >= wf->map_size * 64 || wf->map[(int)x / 64][(int)y / 64])
                y = wf->pl->posy;
            wf->pl->posx = x;
            wf->pl->posy = y;
        }

	if (wf->strafel)
	{
		x = wf->pl->posx;
		y = wf->pl->posy;
		x += cos(degtorad(wf->pl->angle + 90)) * wf->pl->speed;
		if (x < 0 || x >= wf->map_size * 64 || wf->map[(int)x / 64][(int)y / 64])
        	x = wf->pl->posx;
		y -= sin(degtorad(wf->pl->angle + 90)) * wf->pl->speed;
		if (y < 0 || y >= wf->map_size * 64 || wf->map[(int)x / 64][(int)y / 64])
			y = wf->pl->posy;
		wf->pl->posx = x;
		wf->pl->posy = y;
	}

	if (wf->strafer)
	{
		x = wf->pl->posx;
		y = wf->pl->posy;
		x += cos(degtorad(wf->pl->angle - 90)) * wf->pl->speed;
		if (x < 0 || x >= wf->map_size * 64 || wf->map[(int)x / 64][(int)y / 64])
        	x = wf->pl->posx;
		y -= sin(degtorad(wf->pl->angle - 90)) * wf->pl->speed;
		if (y < 0 || y >= wf->map_size * 64 || wf->map[(int)x / 64][(int)y / 64])
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
	float br;

	//ceiling
	color = 0x303030;
	i = 0;
	while (i < data->height / 2)
	{
		br = (float)((float)((data->height / 2) - i) / (float)(data->height / 2));
		j = 0;
		while (j < data->width)
		{
			data->sdl->pix[i * data->width + j] = rgb_multiply(color, br);
			j++;
		}
		i++;
	}
	//floor
	color = 0xffffff;
	i = data->height - 1;
	while (i > data->height / 2)
	{
		j = 0;
		br = (float)((float)(i - data->height / 2) / (float)(data->height / 2));
		while (j < data->width)
		{
			data->sdl->pix[i * data->width + j] = rgb_multiply(color, br);
			j++;
		}
		i--;
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
	init_player(wf);

	init_textures(wf);

	wf->sdl = (t_sdl*)malloc(sizeof(t_sdl));
	prepare_window(wf);

	floor_and_ceiling(wf);
	test(wf);

	while (1)
	{
	    if (wf->strafel || wf->strafer || wf->down || wf->up || wf->right || wf->left)
        {
            memset(wf->sdl->pix, 0, wf->width * wf->height * sizeof(Uint32));
            movement(wf);
			floor_and_ceiling(wf);
            test(wf);
        }
		handle_events(wf);
	}
	return (0);
}
