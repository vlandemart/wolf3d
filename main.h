/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 15:39:50 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 19:52:05 by ydavis           ###   ########.fr       */
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
# define SQLEN 64
//Function defines
# define RAN(l, h) (l + (h - l) * ((double)rand() / RAND_MAX * 2.0 - 1.0))
# define MIN(a, b) ((a < b) ? a : b)
# define MAX(a, b) ((a > b) ? a : b)
# define CLAMP(a, mi, ma) MIN(MAX(a, mi), ma)
# define WRAP(a, wr) ((a < 0) ? a + wr : ((a > wr - 1) ? a - wr : a))
//Texture defines
# define TXT_BRICK 0
# define TXT_WOOD 1
# define TXT_STONE 2
# define TXT_IMG 3
# define TXT_LAMP 4
# define TXT_BOX 5
# define TXT_HEALTH 6
# define TXT_VENT 7
# define TXT_SKY 9

typedef struct	s_v2
{
	float		x;
	float		y;
}				t_v2;

typedef struct	s_pix
{
	int		index;
	int		color;
	int		zbuf;
	int		wall;
	double	dist;
}				t_pix;

typedef struct	s_pl
{
	t_v2	pos;
	double	angle;
	double	fov;
	double	height;
	int		speed;
	int		turn;
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
	int		*floor;
	int		*ceil;
	int		dist;
	int		lov;
	double	angw;
	int		**textures;
	int     left;
	int     right;
	int     up;
	int     down;
	int		strafer;
	int		strafel;
	float	light_distance;
	float	*zbuf;
	t_list	*objects;
	float	ftime;
	float	ftime_old;
	float	frametime;
	float	time;
	int		anim_frame;
	float	flash;
}				t_wf;

typedef struct	s_obj
{
	t_v2	pos_map;
	t_v2	pos_real;
	int		passable;
	int		type;
	int		(*on_col)(void *wf, void *data);
	int		tx;
	int		instance_index;
	int		enabled;
}				t_obj;


/*
**	Prototypes
*/

double			degtorad(double deg);
double			radtodeg(double rad);

t_v2			new_v2(float x, float y);

int				read_map(t_wf *data, char *file_name);
int				*read_texture(char *file_name);

int				rgb_multiply(int rgb, float value);
int				rgb_mix(int rgb1, int rgb2, float percent);

void			update(t_wf *wf, int flag);

//void			put_pixel(t_wf *wf, int index, int color, double dist, int zbuf);
void			put_pixel(t_wf *wf, t_pix pix);

int				raycast(t_wf *data, float angle, float *dist, t_v2 *hit_pos, int *side, int mask);
void			draw_wall(t_wf *wf, int i, double dist, int check, double param);
void			draw_walls(t_wf *wf);
void			draw_objects(t_wf *wf);
void			draw_sky(t_wf *wf);
int				check_collision(t_wf *wf, t_v2 pos);

void			init_textures(t_wf *wf);
int				get_tx(t_wf *wf, int tx_index, int x, int y);


#endif
