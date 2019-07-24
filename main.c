
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

	if (index < 0 || index > wf->height * wf->width)
		return ;
	if (color == 0xff00ff)
		return;
	if (wf->zbuf[index] != 0 && wf->zbuf[index] < dist)
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

int		render_walls(t_wf *wf, double omega, t_v2 *end, int i)
{
    int check;
	int ret;
    t_v2	dist;
	t_v2	move;
	double towall;
	double length;
	double	send;

// MAKE A CLEAN UP, CHECK t_v2, DO EVERYTHING WITH IT

    length = pow(wf->lov, 2);
	check = 0;
	ret = 0;
	end->x = wf->pl->posx;
	end->y = wf->pl->posy;
	move.x = cos(degtorad(omega));
	move.y = -sin(degtorad(omega));
	dist.x = 0.0;
	dist.y = 0.0;

	while (end->x >= 0 && end->y >= 0 && end->x < wf->map_size * SQLEN &&
		end->y < wf->map_size * SQLEN &&
		pow(dist.x, 2) + pow(dist.y, 2) < length)
	{
		if (wf->map[(int)(end->x / SQLEN)][(int)(end->y / SQLEN)] == 2 &&
				(int)end->x % SQLEN < 40 && (int)end->x % SQLEN > 20 &&
				(int)end->y % SQLEN < 40 && (int)end->y % SQLEN > 20)
			ret++;
		if (wf->map[(int)(end->x / SQLEN)][(int)(end->y / SQLEN)] == 1)
		{
			if ((int)(end->x - move.x) / SQLEN > (int)end->x / SQLEN)
			{
				send = end->y;
				check = 1;
			}
			else if ((int)(end->x - move.x) / SQLEN < (int)end->x / SQLEN)
			{
				send = end->y;
				check = 2;
			}
			else if ((int)(end->y - move.y) / SQLEN > (int)end->y / SQLEN)
			{
				send = end->x;
				check = 3;
			}
			else
			{
				send = end->x;
				check = 4;
			}
			break ;
		}
		end->x += move.x;
		end->y += move.y;
		dist.x += move.x;
		dist.y += move.y;
	}

	towall = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
	towall = fabs(towall * cos(degtorad(omega - wf->pl->angle)));
	if (check)
		draw_wall(wf, i, towall, check, send);
	return (ret);
}

void	draw_sprite(t_wf *wf, int i, double dist)
{
	int col;
	int j;
	double shading;
	int		height;
	int		tmp;

	col = 0xffffff;
	j = 0;
	shading = 1 - (MIN(dist, wf->light_distance) / wf->light_distance);
	height = SQLEN * wf->dist / dist / 2;
	tmp = (wf->height - height) / 4;
	while (j < wf->height)
	{
		if (j > tmp * 3 && j < tmp * 4)
			wf->sdl->pix[i + wf->width * j] = rgb_multiply(col, shading);
		j++;
	}
}

void	render_sprites(t_wf *wf, double omega, int sprites, t_v2 start, int i)
{
	(void)wf;
	(void)omega;
	(void)sprites;
	(void)start;
	(void)i;

/*  
	// IT IS FULL OF SHIT! I'LL MAKE A GOOD VERSION WHEN I FIGURE OUT A BETTER WAY TO DO IT
	t_v2 move;
	double dist;

	move.x = cos(degtorad(omega));
	move.y = -sin(degtorad(omega));
	printf("%f %f %f %f -> %f %f\n", move.x, move.y, start.x, start.y, wf->pl->posx, wf->pl->posy);
	while (sprites || (int)start.x != (int)wf->pl->posx || (int)start.y != (int)wf->pl->posy)
	{
		if (wf->map[(int)(start.x / SQLEN)][(int)(start.y / SQLEN)] == 2 &&
				(int)start.x % SQLEN < 40 && (int)start.x % SQLEN > 20 &&
				(int)start.y % SQLEN < 40 && (int)start.y % SQLEN > 20)
		{
			dist = sqrt(pow(start.x - wf->pl->posx, 2) + pow(start.y - wf->pl->posy, 2));
			dist = fabs(dist * cos(degtorad(omega - wf->pl->angle)));
			draw_sprite(wf, i, dist);
			sprites--;
		}
		start.x -= move.x;
		start.y -= move.y;
	}
*/

	/*
	(void)wf;
	(void)omega;
	(void)sprites;
	(void)start;
	*/
// STOPPED HERE, TRY TO MAKE ALL SPRITES	
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
	distfeet /= SQLEN / 2;
	x = wf->pl->posx + (distfeet * cos(degtorad(omega)));
	y = wf->pl->posy + (distfeet * -sin(degtorad(omega)));
	x0 = (int)x % (SQLEN / 2);
	y0 = (int)y % (SQLEN / 2);
	if (x0 < 0)
		x0 += 32;
	if (x0 >= 32)
		x0 -= 32;
	if (y0 >= 32)
		y0 -= 32;
	if (y0 < 0)
		y0 += 32;
	shading = 1 - (MIN(distfeet, wf->light_distance) / wf->light_distance);
	return (rgb_multiply(wf->tx2[x0][y0], shading));
}

void	draw_floor(t_wf *wf)
{
	int i;
	int j;
	double distfeet;
	double height;
	double omega;

	height = wf->height / 2;
	omega = -(wf->pl->fov / 2);
	i = 0;
	while (i < wf->width)
	{
		j = wf->floor[i];
		while (j < wf->height)
		{
			distfeet = (height * wf->dist) / ((j - wf->height / 2) * cos(degtorad(omega)));
			wf->sdl->pix[i + j * wf->width] = find_floor(wf, omega, distfeet);//0xffffff;
			j++;
		}
		i++;
		omega += wf->angw;
	}
}

void	render_all(t_wf *wf)
{
	int		i;
	int		sprites;
	double	omega;
	t_v2	end;

	i = 0;
    omega = wf->pl->angle + wf->pl->fov / 2;
    if (omega >= 360)
        omega -= 360;
	//draw_walls(wf);
	while (i < wf->width)
	{
		end.x = 0;
		end.y = 0;
		sprites = render_walls(wf, omega, &end, i);
		if (sprites)
			render_sprites(wf, omega, sprites, end, i);
		i++;
		omega -= wf->angw;
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
	color = 0x909090;
	i = data->height - 1;
	while (i > data->height / 2)
	{
		j = 0;
		br = (float)((float)(i - data->height / 2) / (float)(data->height / 2));
		while (j < data->width)
		{
			data->sdl->pix[i * data->width + j] = rgb_multiply(color, br);
	//render_all(wf);
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
	//render_all(wf);

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
			draw_objects(wf);
			update(wf, 0);
            //render_all(wf);
        }
		handle_events(wf);
	}
	return (0);
}
