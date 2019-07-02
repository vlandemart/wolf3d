
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
}

double	degtorad(double deg)
{
	return (deg * (M_PI / 180));
}

double	check_y(t_wf *wf, double omega)
{
	int		check;
	double	x;
	double	y;
	double	disty;
	double	movey;

	check = 0;
	disty = wf->map_size * 600;
	if (omega == 270 || omega == 90 || omega == 180 || omega == 0)
        return (disty);
	if (omega < 90 || omega > 270)
    {
		x = floor(wf->pl->posx / 64) * 64 + 64;
		y = wf->pl->posy + (wf->pl->posx - x) * tan(degtorad(omega));
    }
	else
    {
		x = floor(wf->pl->posx / 64) * 64;
        y = wf->pl->posy + (wf->pl->posx - x) * tan(degtorad(omega));
        x--;
    }
	movey = tan(degtorad(omega)) * 64;
	while (!check &&
			x > 0 &&
			y > 0 &&
			pow(x - wf->pl->posx, 2) + pow(y - wf->pl->posy, 2) <
			pow(wf->lov, 2) &&
			x < wf->map_size * 64 &&
			y < wf->map_size * 64)
	{
		if (wf->map[(int)(x / 64)][(int)(y / 64)])
		{
			check = 1;
			break ;
		}
		if (omega < 90 || omega > 270)
			x += 64;
		else
			x -= 64;
		y += movey;
	}
	if (check == 1)
		disty = fabs(wf->pl->posx - x) / cos(degtorad(omega));// * cos(degtorad(omega - wf->pl->angle));
    //printf("disty = %f\n", disty);
    if (disty < 0)
        disty = -disty;
    //printf("disty = %f\n", disty);
	return (disty);
}

double  check_x(t_wf *wf, double omega)
{
    double  dist;
    int     check;
    double  x;
    double  y;
    double  xmove;
    double  ymove;

    check = 0;
    dist = wf->map_size * 600;
    if (omega == 90 || omega == 270 || omega == 180 || omega == 0)
        return (dist);
    if (omega > 180 || omega < 0)
    {
        y = floor(wf->pl->posy / 64) * 64 + 64;
        x = wf->pl->posx + (wf->pl->posy - y) / tan(degtorad(omega));
    }

    else
    {
        y = floor(wf->pl->posy / 64) * 64;
        x = wf->pl->posx + (wf->pl->posy - y) / tan(degtorad(omega));
        y--;
    }
    xmove = 64 / tan(degtorad(omega));
    while (!check &&
            x > 0 &&
            y > 0 &&
            pow(x - wf->pl->posx, 2) + pow(y - wf->pl->posy, 2) <
            pow(wf->lov, 2) &&
            x < wf->map_size * 64 &&
            y < wf->map_size * 64)
    {
        if (wf->map[(int)(x / 64)][(int)(y / 64)])
        {
            check = 1;
            break ;
        }
        if (omega > 180)
            y += 64;
        else
            y -= 64;
        x += xmove;
    }
    if (check)
        dist = fabs(wf->pl->posy - y) / sin(degtorad(omega));// * cos(degtorad(omega - wf->pl->angle));
   // printf("omega = %f    distx = %f    ", omega, dist);
    if (dist < 0)
        dist = -dist;
    //printf("omega = %f    distx = %f    ", omega, dist);
    return (dist);
}

void	fill_col(t_wf *wf, int i, double dist, int col)
{
	int j;
	int	height;
	int	tmp;
	float shading;

	shading = 1 - (MIN(dist, wf->light_distance) / wf->light_distance);
	height = SQLEN * wf->dist / dist / 2;
	tmp = (wf->height - height) / 2;
	j = 0;
	while (j < wf->height)
	{
		if (j > tmp && j < tmp + height)
			wf->sdl->pix[i + wf->width * j] = rgb_multiply(col, shading);
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
        while (x >= 0 && y >= 0 && x < wf->map_size * 64 && y < wf->map_size * 64 && pow(distx, 2) + pow(disty, 2) < tmp)
        {
            if (wf->map[(int)(x / 64)][(int)(y / 64)])
            {
                if ((int)(x - xmove) / 64 > (int)x / 64)
                    col = 0x0000ff;
                else if ((int)(x - xmove) / 64 < (int)x / 64)
                    col = 0x00ff00;
                else if ((int)(y - ymove) / 64 > (int)y / 64)
                    col = 0x00ffff;
                else
                    col = 0xff0000;
		check = 1;
                break ;
            }
            x += xmove;
            y += ymove;
            distx += xmove;
            disty += ymove;
        }
        dist = sqrt(pow(distx, 2) + pow(disty, 2));
       	dist = abs((int)(dist * fabs(cos(degtorad(omega - wf->pl->angle)))));
	if (check)
        	fill_col(wf, i, dist, col);
	omega -= wf->angw;
	    if (omega < 0)
            omega += 360;
		i++;
	}

    /*
	double	omega;
	int		i;
	double	movex;
	double	distx;
	double	disty;
	i = 0;
	omega = wf->pl->angle + wf->pl->fov / 2;
	if (omega >= 360)
        omega -= 360;
	while (i < wf->width)
	{
	    distx = check_x(wf, omega);
	    disty = check_y(wf, omega);
	    fill_col(wf, i, (distx < disty ? distx : disty));
	    omega -= wf->angw;
	    if (omega < 0)
            omega += 360;
        i++;
	}
    */
	    /*
		check = 0;
		if ((omega > 180 || omega < 0) && omega < 360)
			y = floor(wf->pl->posy / 64) * 64 + 64;
		else
			y = floor(wf->pl->posy / 64) * 64 - 1;
		x = wf->pl->posx + (wf->pl->posy - y) / tan(degtorad(omega));
		movex = 64 / tan(degtorad(omega));
		while (!check &&
				x > 0 &&
				y > 0 &&
				pow(x - wf->pl->posx, 2) + pow(y - wf->pl->posy, 2) <
				pow(wf->lov, 2) &&
				x < wf->map_size * 64 &&
				y < wf->map_size * 64)
		{
			if (wf->map[(int)x / 64][(int)y / 64])
			{
				check = 1;
				break ;
			}
			if (omega >= 180)
				y += 64;
			else
				y -= 64;
			x += movex;
		}
		if (check == 1)
		{
			distx = fabs(wf->pl->posx - x) / cos(degtorad(omega)) * cos(degtorad(omega - wf->pl->angle));
			/*
			fill_col(wf, i, distx, omega);
			disty = check_y(wf, omega);
			if (disty < 0)
				fill_col(wf, i, distx, omega);
			else
				fill_col(wf, i, (distx < disty && disty > 0 ? distx : disty), omega);
		}
		disty = check_y(wf, omega);
		if (disty > 0)
			fill_col(wf, i, (distx < disty && distx > 0 ? distx : disty), omega);
		else if (distx > 0)
			fill_col(wf, i, distx, omega);
		omega -= wf->angw;
		if (omega >= 360)
			omega -= 360;
		i++;
		*/

	/*
	while (i < wf->width)
	{
		check = 0;
		distx = 0.0;
		disty = 0.0;
		x = wf->pl->posx;
		y = wf->pl->posy;
		while (x > 0 && y > 0 && x < wf->lov && y < wf->lov)
		{
			if (!((int)x % 64) || !((int)y % 64))
			{
				if (wf->map[(int)x / 64][(int)y / 64])
				{
					printf("%f - %d ; %f - %d\n", x, (int)x, y, (int)y);
					check = (!((int)x % 64) ? 1 : 2);
					break ;
				}
			}
			x += cos(omega);
			y -= sin(omega);
		}
		if (check == 1)
			fill_col(wf, i, distx);
		if (check == 2)
			fill_col(wf, i, disty);
		i++;
		omega += wf->angw;
	}
	*/

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
    int i;
    int j;
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

int	floor_and_ceiling(t_wf *data)
{
	int i;
	int j;
	int color;
	int rgb;
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

int	handle_events(t_wf *wf)
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
			if (SDLK_UP == evt.key.keysym.sym)
				wf->up = 1;
			if (SDLK_DOWN == evt.key.keysym.sym)
				wf->down = 1;
		}
		if (SDL_KEYUP == evt.type)
		{
			if (SDLK_LEFT == evt.key.keysym.sym)
				wf->left = 0;
			if (SDLK_RIGHT == evt.key.keysym.sym)
				wf->right = 0;
			if (SDLK_UP == evt.key.keysym.sym)
				wf->up = 0;
			if (SDLK_DOWN == evt.key.keysym.sym)
				wf->down = 0;
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

	wf->sdl = (t_sdl*)malloc(sizeof(t_sdl));
	prepare_window(wf);

	floor_and_ceiling(wf);
	test(wf);

	while (1)
	{
	    if (wf->down || wf->up || wf->right || wf->left)
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
