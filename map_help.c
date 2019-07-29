/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 22:42:57 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/30 02:07:27 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	txt_type(t_obj *obj, int type)
{
	if (type == 2)
	{
		obj->tx = TXT_BOX;
		obj->on_col = NULL;
		obj->passable = 0;
	}
	else if (type == 3)
	{
		obj->tx = TXT_LAMP;
		obj->on_col = NULL;
		obj->passable = 1;
	}
	else if (type == 4)
	{
		obj->tx = TXT_HEALTH;
		obj->on_col = destroy_obj;
		obj->passable = 1;
	}
}

void	new_map(t_wf *wf)
{
	int i;
	int j;

	ft_putendl("Allocating map...");
	malloc_check(wf, wf->map = (int**)malloc(sizeof(int*) * wf->map_size));
	i = 0;
	while (i < wf->map_size)
	{
		malloc_check(wf, wf->map[i] = (int*)malloc(sizeof(int) * wf->map_size));
		j = 0;
		while (j < wf->map_size)
		{
			wf->map[i][j] = 1;
			j++;
		}
		i++;
	}
	ft_putendl("Binding map values...");
}

void	find_objs(t_wf *wf, char n, int i, int j)
{
	if (ft_isdigit(n))
	{
		if (n - '0' > 1)
			create_obj(wf, i, j, n - '0');
		wf->map[i][j] = n - '0';
	}
}

char	*from_file(int fd, char *str, t_v2 *map_size, char *map)
{
	while (get_next_line(fd, &str) > 0)
	{
		if (ft_strlen(str) > map_size->x)
			map_size->x = ft_strlen(str);
		map = ft_strjoinc(map, str);
		map = ft_strjoinc(map, "\n");
		ft_strdel(&str);
		map_size->y++;
	}
	return (map);
}

void	txt_read(char *str, int *texture, char *tmp)
{
	int		i;
	int		j;
	int		n;

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
			texture[j + i * 32] = ft_atoi(tmp);
			ft_strdel(&tmp);
			n++;
			j++;
		}
		n++;
		i++;
	}
}
