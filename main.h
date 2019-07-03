/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 15:39:50 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/03 15:07:46 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "SDL2/SDL.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "lib/libft/libft.h"
//# include "libft/libft.h"
# define SQLEN 64
# define RAN(l, h) (l + (h - l) * ((double)rand() / RAND_MAX * 2.0 - 1.0))
# define MIN(a, b) ((a < b) ? a : b)
# define MAX(a, b) ((a > b) ? a : b)
# define CLAMP(a, mi, ma) MIN(MAX(a, mi), ma)

typedef struct	s_v2
{
	float		x;
	float		y;
}				t_v2;

typedef struct	s_pl
{
	double	posx;
	double	posy;
	double	angle;
	double	fov;
	int     speed;
	int     turn;
}				t_pl;

typedef struct	s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*sf;
	SDL_Event		evt;
	SDL_Renderer	*ren;
	SDL_Texture		*txt;
	Uint32			*pix;
}				t_sdl;

typedef struct	s_wf
{
	t_sdl	*sdl;
	t_pl	*pl;
	int		width;
	int		height;
	int		**map;
	int		map_size;
	int		dist;
	int		lov;
	double	angw;
	int     left;
	int     right;
	int     up;
	int     down;
	float	light_distance;
}				t_wf;
double			degtorad(double deg);
t_v2			new_v2(int x, int y);
int				read_map(t_wf *data, char *file_name);
int				**read_texture(char *file_name);
int				rgb_add(int rgb, float value);
int				rgb_multiply(int rgb, float value);
#endif
