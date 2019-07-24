/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 15:39:50 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/24 20:47:41 by ydavis           ###   ########.fr       */
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
	double	height;
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

typedef struct	s_obj
{
	t_v2	pos;
	int		passable;
	int		type;
	void	*on_col;
	int		**texture;
}				t_obj;

typedef struct	s_wf
{
	t_sdl	*sdl;
	t_pl	*pl;
	int		width;
	int		height;
	int		**map;
	int		map_size;
	int		*floor;
	int		*ceil;
	int		dist;
	int		lov;
	double	angw;
	int		**tx1;
	int		**tx2;
	int		**tx3;
	int		**tx4;
	int     left;
	int     right;
	int     up;
	int     down;
	int		strafer;
	int		strafel;
	float	light_distance;
	float	*zbuf;
	t_list	*objects;
}				t_wf;

double			degtorad(double deg);
double			radtodeg(double rad);
t_v2			new_v2(float x, float y);
int				read_map(t_wf *data, char *file_name);
int				**read_texture(char *file_name);
int				rgb_add(int rgb, float value);
int				rgb_multiply(int rgb, float value);
void			draw_walls(t_wf *wf);
void			update(t_wf *wf, int flag);
void			draw_wall(t_wf *wf, int i, double dist, int check, double param);
void			draw_objects(t_wf *wf);
int				raycast(t_wf *data, float angle, float *dist, t_v2 *hit_pos, int *side, int mask);
void			put_pixel(t_wf *wf, int index, int color, double dist);

#endif
