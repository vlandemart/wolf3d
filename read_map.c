#include "main.h"

t_v2	new_v2(int x, int y)
{
	t_v2 v2;

	v2.x = x;
	v2.y = y;
	return (v2);
}

int		bind_map(t_wf *data, char *map)
{
	int i;
	int j;
	int n;

	//Allocate array
	printf("Allocating map...\n");
	data->map = (int**)malloc(sizeof(int*) * data->map_size);
	i = 0;
	while (i < data->map_size)
	{
		data->map[i] = (int*)malloc(sizeof(int) * data->map_size);
		ft_bzero(data->map[i], sizeof(int) * data->map_size);
		i++;
	}
	//Bind corresponding values
	printf("Binding map values...\n");
	n = 0;
	i = 0;
	while (map[n])
	{
		j = 0;
		while (map[n] != '\n')
		{
			if (ft_isdigit(map[n]))
			{
				//printf("Binding map value in %d:%d to %d\n", i, j, map[n]);
				data->map[i][j] = map[n] - '0';
			}
			n++;
			j++;
		}
		while (j < data->map_size)
			data->map[i][j++] = 0;
		n++;
		i++;
	}
	return (1);
}

int		read_map(t_wf *data, char *file_name)
{
	int		fd;
	char	*str;
	char	*map;
	t_v2	map_size;

	printf("Opening map...\n");
	fd = open(file_name, O_RDONLY);
	map = ft_strnew(0);
	map_size = new_v2(0, 0);
	if (fd <= 0)
	{
		printf("Error opening map!\n");
		return (0);
	}
	printf("Reading map...\n");
	while (get_next_line(fd, &str) > 0)
	{
		if (ft_strlen(str) > map_size.x)
		{
			//printf("prev %f, curr %d\n", map_size.x, (int)ft_strlen(str));
			map_size.x = ft_strlen(str);
		}
		map = ft_strjoinc(map, str);
		map = ft_strjoinc(map, "\n");
		ft_strdel(&str);
		map_size.y++;
	}
	printf("Read map:\n%s\n", map);
	printf("Binding map...\n");
	data->map_size = MAX(map_size.x, map_size.y);
	bind_map(data, map);
	printf("Map clean up...\n");
	ft_strdel(&map);
	printf("Map read!\n");
	return (1);
}