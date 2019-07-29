/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 19:33:23 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/29 22:31:11 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		destroy_obj(void *data_wf, void *data_obj)
{
	t_wf	*wf;
	t_obj	*obj_to_destroy;
	t_obj	*obj;
	t_list	*objs;

	wf = (t_wf*)data_wf;
	obj_to_destroy = (t_obj*)data_obj;
	objs = wf->objects;
	while (objs != NULL)
	{
		obj = (t_obj*)(objs->content);
		if (obj->instance_index == obj_to_destroy->instance_index)
			obj->enabled = 0;
		objs = objs->next;
	}
	wf->flash = 0.7;
	wf->score += 1;
	ft_putstr("Score: ");
	ft_putnbr(wf->score);
	ft_putstr("/");
	ft_putnbr(wf->score_max);
	ft_putstr("\n");
	if (wf->score == wf->score_max)
		ft_putstr("You won!\n");
	return (0);
}

int		create_obj(t_wf *wf, int x, int y, int type)
{
	t_obj *obj;

	malloc_check(wf, obj = (t_obj*)malloc(sizeof(t_obj)));
	obj->pos_map = new_v2(x, y);
	obj->pos_real = new_v2((obj->pos_map.x + 0.5f) * SQLEN,
			(obj->pos_map.y + 0.5f) * SQLEN);
	obj->instance_index = x + y * wf->map_size;
	obj->enabled = 1;
	txt_type(obj, type);
	if (type == 4)
		wf->score_max += 1;
	ft_lstadd(&wf->objects, ft_lstnew(obj, sizeof(t_obj)));
	free(obj);
	return (1);
}

int		bind_map(t_wf *data, char *map)
{
	int i;
	int j;
	int n;

	new_map(data);
	n = 0;
	i = 0;
	while (map[n])
	{
		j = 0;
		while (map[n] != '\n')
		{
			find_objs(data, map[n], i, j);
			n++;
			j++;
		}
		while (j < data->map_size)
			data->map[i][j++] = 0;
		n++;
		i++;
	}
	ft_putnbr(ft_lstcount(data->objects));
	ft_putendl(" objects detected on map.");
	return (1);
}

int		read_map(t_wf *data, char *file_name)
{
	int		fd;
	char	*str;
	char	*map;
	t_v2	map_size;

	str = NULL;
	ft_putendl("Opening map...");
	fd = open(file_name, O_RDONLY);
	map = ft_strnew(0);
	map_size = new_v2(0, 0);
	if (fd <= 0)
		return (0);
	ft_putendl("Reading map...");
	map = from_file(fd, str, &map_size, map);
	ft_putendl("Read map:");
	ft_putendl(map);
	ft_putendl("Binding map...");
	data->map_size = (int)max(map_size.x, map_size.y);
	bind_map(data, map);
	ft_putendl("Map clean up...");
	ft_strdel(&map);
	ft_putendl("Map read!");
	return (1);
}

int		*read_texture(t_wf *wf, char *file_name)
{
	int		n;
	char	*tmp;
	char	*str;
	int		*texture;

	n = open(file_name, O_RDONLY);
	if (n <= 0)
		return (NULL);
	str = ft_strnew(0);
	while (get_next_line(n, &tmp) > 0)
	{
		str = ft_strjoinc(str, tmp);
		str = ft_strjoinc(str, "\n");
		ft_strdel(&tmp);
	}
	malloc_check(wf, texture = (int*)malloc(sizeof(int) * 32 * 32));
	txt_read(str, texture, tmp);
	free(str);
	free(tmp);
	ft_putstr(file_name);
	ft_putendl(" was loaded.");
	return (texture);
}
