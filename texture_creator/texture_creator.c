#include <SDL2/SDL.h>
#include "../lib/libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define SCREEN_W 640
#define SCREEN_H 640
#define IMAGE_SIZE 32
#define FALSE 0
#define TRUE 1
#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)
#define CLAMP(a, mi, ma) MIN(MAX(a, mi), ma)

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

int			close_app(t_data *data, char *die_msg)
{
	SDL_DestroyWindow(data->win);
	SDL_Quit();

	printf("%s\n", die_msg);
	exit(1);
}

t_data	*init_sdl()
{
	t_data	*data;

	data = (t_data*)malloc(sizeof(t_data));
	SDL_Init(SDL_INIT_VIDEO);
	data->win = SDL_CreateWindow
	(
		"Texture creator",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_W,
		SCREEN_H,
		SDL_WINDOW_OPENGL
	);
	if (!data->win)
		close_app(data, "SDL can't open window.");
	data->rend = SDL_CreateRenderer
	(
		data->win, -1,
		SDL_RENDERER_SOFTWARE
	);
	if (!data->rend)
		close_app(data, "SDL can't create renderer.");
	data->texture = SDL_CreateTexture
	(
		data->rend,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_W, SCREEN_H
	);
	data->pixel = malloc(SCREEN_H * SCREEN_H * sizeof(int));
	data->pixel_size = 20;
	data->selected_color = 0xFF0000;
	data->file_name = "img";

	return (data);
}

int			export_image(t_data *data)
{
	int i;
	int j;
	int fd;
	char *file_name;
	char *str;

	if (open(data->file_name, O_RDONLY))
		remove(data->file_name);
	fd = open(data->file_name, O_WRONLY | O_CREAT, 444);
	str = ft_strnew(0);
	i = 0;
	while (i < IMAGE_SIZE)
	{
		j = 0;
		while (j < IMAGE_SIZE)
		{
			str = ft_strjoinc(str, ft_itoa(data->image[i][j]));
			str = ft_strjoinc(str, " ");
			j++;
		}
		str = ft_strjoinc(str, "\n");
		i++;
	}
	str = ft_strjoinc(str, "\0");
	write(fd, str, ft_strlen(str) * sizeof(char));
	close(fd);
	close_app(data, "Image exported!");
	return (1);
}

int			render(t_data *data)
{
	SDL_UpdateTexture
	(
		data->texture,
		NULL,
		data->pixel,
		SCREEN_W * 4
	);
	SDL_RenderClear(data->rend);
	SDL_RenderCopy(data->rend, data->texture, NULL, NULL);
	SDL_RenderPresent(data->rend);
	return (1);
}

int			draw_grid(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < SCREEN_H)
	{
		j = 0;
		while(j < SCREEN_W)
		{
			if (i % data->pixel_size == 0 || j % data->pixel_size == 0)
				data->pixel[SCREEN_W * j + i] = 0x303030;
			j++;
		}
		i++;
	}
	return (0);
}

int			pick_color(t_data *data, int x, int y)
{
	data->selected_color = data->pixel[SCREEN_W * y + x];
	return (1);
}

int			set_pixel(t_data *data, int x, int y)
{
	int i;
	int j;
	int block_end;
	int has_changed;

	has_changed = FALSE;
	i = x / data->pixel_size * data->pixel_size;
	while (i < ((x / data->pixel_size) * data->pixel_size + data->pixel_size))
	{
		j = (y / data->pixel_size) * data->pixel_size;
		while (j < ((y / data->pixel_size) * data->pixel_size + data->pixel_size))
		{
			if (data->pixel[SCREEN_W * j + i] != data->selected_color)
				has_changed = TRUE;
			data->pixel[SCREEN_W * j + i] = data->selected_color;
			data->image[y / data->pixel_size][x / data->pixel_size] = data->selected_color;
			j++;
		}
		i++;
	}
	if (has_changed == TRUE)
		render(data);
	return (1);
}

int	rgb_split(int rgb, int *r, int *g, int *b)
{
	*r = (rgb >> 16) & 0xff;
	*g = (rgb >> 8) & 0xff;
	*b = rgb & 0xff;

	return (1);
}

int	rgb_compose(int r, int g, int b)
{
	int rgb;

	rgb = 0;
	rgb = rgb | (r << 16);
	rgb = rgb | (g << 8);
	rgb = rgb | b;
	return (rgb);
}

int	rgb_add(int rgb, int rr, int gg, int bb)
{
	int r;
	int g;
	int b;
	int new_rgb;

	rgb_split(rgb, &r, &g, &b);
	r = CLAMP((int)((float)r + rr), 0, 255);
	g = CLAMP((int)((float)g + gg), 0, 255);
	b = CLAMP((int)((float)b + bb), 0, 255);
	rgb = rgb_compose(r, g, b);
	return (rgb);
}

int			change_color(t_data *data, int wheel)
{
	int r;
	int g;
	int b;

	r = (data->color_added == 1) ? 20 * wheel : 0;
	g = (data->color_added == 2) ? 20 * wheel : 0;
	b = (data->color_added == 3) ? 20 * wheel : 0;
	if (data->color_added == 4)
	{
		r = 10 * wheel;
		g = 10 * wheel;
		b = 10 * wheel;
	}
	CLAMP(wheel, -1, 1);
	data->selected_color = rgb_add(data->selected_color, r, g, b);
	rgb_split(data->selected_color, &r, &g, &b);
	printf("New color is %d : %d : %d\n", r, g, b);
	return (1);
}

int			event_handle(t_data *data)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			close_app(data, "App was closed.");
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				data->button_held = TRUE;
			else
				pick_color(data, event.motion.x, event.motion.y);
		}
		if (event.type == SDL_MOUSEBUTTONUP)
			data->button_held = FALSE;
		if (event.type == SDL_MOUSEMOTION && data->button_held)
			set_pixel(data, event.motion.x, event.motion.y);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
				draw_grid(data);
			if (event.key.keysym.sym == SDLK_1)
				data->color_added = 1;
			if (event.key.keysym.sym == SDLK_2)
				data->color_added = 2;
			if (event.key.keysym.sym == SDLK_3)
				data->color_added = 3;
			if (event.key.keysym.sym == SDLK_4)
				data->color_added = 4;
			if (event.key.keysym.sym == SDLK_l ||
				event.key.keysym.sym == SDLK_KP_PLUS)
				export_image(data);
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_1 ||
				event.key.keysym.sym == SDLK_2 ||
				event.key.keysym.sym == SDLK_3)
				data->color_added = 0;
		}
		if (event.type == SDL_MOUSEWHEEL)
			change_color(data, event.wheel.y);

	}
	return (1);
}

int			update(t_data *data)
{
	while (TRUE)
	{
		event_handle(data);
		render(data);
	}
	return (1);
}

int			open_file(t_data *data)
{
	int n;
	char *tmp;
	char *str;
	int i;
	int j;

	n = open(data->file_name, O_RDONLY);
	if (n <= 0)
		return (0);
	str = ft_strnew(0);
	printf("Reading image...\n");
	while (get_next_line(n, &tmp) > 0)
	{
		str = ft_strjoinc(str, tmp);
		str = ft_strjoinc(str, "\n");
		ft_strdel(&tmp);
	}
	printf("Image read.\n");
	printf("Opening image...\n");
	i = 0;
	n = 0;
	while (str[n])
	{
		j = 0;
		while (str[n] && str[n] != '\n')
		{
			tmp = ft_strnew(0);
			while (isdigit(str[n]))
			{
				tmp = ft_strjoinc(tmp, &str[n]);
				n++;
			}
			data->selected_color = ft_atoi(tmp);
			set_pixel(data, j * data->pixel_size, i * data->pixel_size);
			ft_strdel(&tmp);
			n++;
			j++;
		}
		n++;
		i++;
	}
	printf("Image opened.\n");
	return (1);
}

int			main(int ac, char **av)
{
	t_data *data;

	data = init_sdl();
	printf("======\n");
	printf("Usage: \n Hold 1-3 and scroll mouse to modify rgb channels \n Hold 4 and scroll mouse to darken/lighten current color \n LMB presses selected color, RMB copies color under cursor \n Press Space to renew image's grid \n Press L to export image. Image name is set in opening argument\n If image with that name exists, opens it instead\n");
	printf("======\n");
	if (ac == 2)
	{
		data->file_name = av[1];
		if (!open_file(data))
			memset(data->pixel, 0x000000, SCREEN_W * SCREEN_H * sizeof(int));
	}
	else
	{
		memset(data->pixel, 0x000000, SCREEN_W * SCREEN_H * sizeof(int));
	}
	update(data);
	return (1);
}
