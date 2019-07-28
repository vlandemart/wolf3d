/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 15:39:50 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 22:28:06 by ydavis           ###   ########.fr       */
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

typedef struct	s_wall
{
	int		i;
	int		side;
	double	dist;
	double	param;
}				t_wall;

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

double			ran(double l, double h);
double			min(double a, double b);
double			max(double a, double b);
double			clamp(double a, double mi, double ma);

t_v2			new_v2(float x, float y);
t_wall			new_wall(int i, double dist, int side, double param);
t_pix			new_pix(int index, double dist, int zbuf, int wall);

t_wf			*init_wf(int ac, char **av);
void			init_map(t_wf *wf);
void			init_player(t_wf *wf);
void			init_floorceil(t_wf *wf);
void			init_args(t_wf *wf, int ac, char **av);
void			prepare_window(t_wf *wf);
void			floor_and_ceiling(t_wf *wf);
void			malloc_check(t_wf *wf, void *addr);

int				read_map(t_wf *data, char *file_name);
int				*read_texture(char *file_name);

int				rgb_multiply(int rgb, float value);
int				rgb_mix(int rgb1, int rgb2, float percent);

void			update(t_wf *wf, int flag);

void			movement(t_wf *wf);
void			move_up(t_wf *wf);
void			move_down(t_wf *wf);
void			turn_left(t_wf *wf);
void			turn_right(t_wf *wf);
void			strafe_left(t_wf *wf);
void			strafe_right(t_wf *wf);

void			put_pixel(t_wf *wf, t_pix pix);
void			render(t_wf *wf);

int				raycast(t_wf *data, float angle, float *dist, t_v2 *hit_pos, int *side, int mask);
void			draw_wall(t_wf *wf, t_wall wall);
void			draw_walls(t_wf *wf);
void			draw_objects(t_wf *wf);
void			draw_ceilfloor(t_wf *wf);
int				floor_ceil(t_wf *wf, double omega, double distfeet, int txt);
void			draw_sky(t_wf *wf);
int				check_collision(t_wf *wf, t_v2 pos);

void			init_textures(t_wf *wf);
int				get_tx(t_wf *wf, int tx_index, int x, int y);

int				cycle(t_wf *wf);
void			handle_events(t_wf *wf);
void			calculate_frametime(t_wf *wf);
void			time_update(t_wf *wf);
void			malloc_check(t_wf *wf, void *addr);
int				close_app_s(t_wf *wf, char *str);

#endif
