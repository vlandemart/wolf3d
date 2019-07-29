/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_creator.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 19:23:34 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/29 21:01:48 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_CREATOR_H
# define TEXTURE_CREATOR_H
# define SCREEN_W 640
# define SCREEN_H 640
# define IMAGE_SIZE 32
# define FALSE 0
# define TRUE 1
# include "SDL2/SDL.h"
# include "lib/libft/libft.h"
# include "fcntl.h"
# include "unistd.h"
# include "stdlib.h"

typedef struct	s_data
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Texture		*texture;
	int				*pixel;
	int				image[IMAGE_SIZE][IMAGE_SIZE];
	int				button_held;
	int				pixel_size;
	int				selected_color;
	int				color_added;
	char			*file_name;
}				t_data;
int				txt_update(t_data *data);
int				txt_render(t_data *data);
int				event_handle(t_data *data);
void			check_malloc(void *addr);
int				pick_color(t_data *data, int x, int y);
int				draw_grid(t_data *data);
int				rgb_compose(int r, int g, int b);
int				rgb_split(int rgb, int *r, int *g, int *b);
int				rgb_add(int rgb, int rr, int gg, int bb);
int				exit_msg(t_data *data, char *die_msg);
int				set_pixel(t_data *data, int x, int y);
int				export_image(t_data *data);
int				change_color(t_data *data, int y);
int				open_file(t_data *data);
double			clamp(double a, double mi, double ma);
#endif
