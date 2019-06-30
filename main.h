/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 15:39:50 by ydavis            #+#    #+#             */
/*   Updated: 2019/06/29 00:56:12 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <SDL2/SDL.h>
# include <math.h>
# include <stdlib.h>
# include "libft/libft.h"
# define SQLEN 64
# define MAPL 10 // DELETE AFTER
# define RAN(l, h) (l + (h - l) * ((double)rand() / RAND_MAX * 2.0 - 1.0))

typedef struct	s_pl
{
	double	posx;
	double	posy;
	double	angle;
	double	fov;
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
	int		dist;
	int		lov;
	double	angw;
}				t_wf;
double			degtorad(double deg);
#endif
