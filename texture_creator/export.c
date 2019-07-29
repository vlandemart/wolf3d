/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 20:30:16 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/29 20:53:05 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_creator.h"

int		export_image(t_data *data)
{
	int		i;
	int		j;
	int		fd;
	char	*str;

	if (open(data->file_name, O_RDONLY))
		remove(data->file_name);
	fd = open(data->file_name, O_WRONLY | O_CREAT, 444);
	str = ft_strnew(0);
	i = -1;
	while (++i < IMAGE_SIZE)
	{
		j = -1;
		while (++j < IMAGE_SIZE)
		{
			str = ft_strjoinc(str, ft_itoa(data->image[i][j]));
			str = ft_strjoinc(str, " ");
		}
		str = ft_strjoinc(str, "\n");
	}
	str = ft_strjoinc(str, "\0");
	write(fd, str, ft_strlen(str) * sizeof(char));
	close(fd);
	exit_msg(data, "Image exported!");
	return (1);
}

char	*read_from(int fd)
{
	char	*str;
	char	*tmp;

	while (get_next_line(fd, &tmp) > 0)
	{
		str = ft_strjoinc(str, tmp);
		str = ft_strjoinc(str, "\n");
		ft_strdel(&tmp);
	}
	return (str);
}

char	*fill_str(char *str, int *n)
{
	char *ret;

	ret = ft_strnew(0);
	while (isdigit(str[*n]))
		ret = ft_strjoinc(ret, &str[*n++]);
	return (ret);
}

int		open_cycle(t_data *data, int *i, int *n, char *str)
{
	int		j;
	char	*tmp;

	j = 0;
	while (str[*n] && str[*n] != '\n')
	{
		tmp = fill_str(str, n);
		data->selected_color = ft_atoi(tmp);
		set_pixel(data, j * data->pixel_size, *i * data->pixel_size);
		ft_strdel(&tmp);
		*n = *n + 1;
	}
	return (0);
}

int		open_file(t_data *data)
{
	int		n;
	int		i;
	char	*str;

	n = open(data->file_name, O_RDONLY);
	if (n <= 0)
		return (0);
	str = read_from(n);
	i = 0;
	n = 0;
	while (str[n])
	{
		open_cycle(data, &i, &n, str);
		n++;
		i++;
	}
	return (1);
}
