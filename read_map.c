#include "main.h"

t_v2	new_v2(float x, float y)
{
	t_v2 v2;

	v2.x = x;
	v2.y = y;
	return (v2);
}

int		create_obj(t_wf *wf, int x, int y, int type)
{
	t_obj *obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj->pos = new_v2(x, y);
	if (type == 2)
	{
		obj->texture = read_texture("texture_creator/box.wolf");
		obj->on_col = NULL;
		obj->passable = 1;
	}
	//TODO: put created object into wf->objects
	ft_lstadd(&wf->objects, ft_lstnew(obj, sizeof(t_obj)));
	return (1);
}

int		bind_map(t_wf *data, char *map)
{
	int i;
	int j;
	int n;
	int type;

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
				type = map[n] - '0';
				if (type > 1)
					create_obj(data, i, j, type);
				data->map[i][j] = type;
			}
			n++;
			j++;
		}
		while (j < data->map_size)
			data->map[i][j++] = 0;
		n++;
		i++;
	}
	printf("Objects detected on map: %d\n", ft_lstcount(data->objects));
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

int	**read_texture(char *file_name)
{
	int		n;
	char	*tmp;
	char	*str;
	int		i;
	int		j;
	int		**texture;

	n = open(file_name, O_RDONLY);
	if (n <= 0)
		return (NULL);
	str = ft_strnew(0);
	//printf("Reading texture...\n");
	while (get_next_line(n, &tmp) > 0)
	{
		str = ft_strjoinc(str, tmp);
		str = ft_strjoinc(str, "\n");
		ft_strdel(&tmp);
	}
	//printf("Texture read.\n");
	//printf("Opening texture...\n");
	texture = (int**)malloc(sizeof(int*) * 32);
	i = 0;
	while (i < 32)
	{
		texture[i] = (int*)malloc(sizeof(int) * 32);
		i++;
	}
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
			texture[j][i] = ft_atoi(tmp);
			ft_strdel(&tmp);
			n++;
			j++;
		}
		n++;
		i++;
	}
	printf("%s was loaded.\n", file_name);
	return (texture);
}