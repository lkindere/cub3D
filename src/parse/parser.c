/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:34:16 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/23 07:13:28 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Returns 1 on valid line
//Returns 0 on empty line
//Returns -1 on error
int	check_line(t_map *map, char *line)
{
	if (check_empty(line) == 1)
	{
		if (map->map[0])
			return (invalidate_map(map, INVALID_MAP_FORMAT));
		return (0);
	}
	if (get_textures(map, line) == 1)
		return (1);
	if (map->valid != VALID)
		return (-1);
	if (get_colors(map, line) == 1)
		return (1);
	if (map->valid != VALID)
		return (-1);
	return (get_map(map, line));
}

//Returns 1 on valid map
//Returns -1 on invalid map
int	read_map(t_map *map, char **argv)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (invalidate_map(map, NO_MAP));
	while (get_line(fd, &line) > 0 && check_line(map, line) != -1)
	{
		free(line);
		line = NULL;
		if (map->valid != VALID)
		{
			close(fd);
			return (-1);
		}
	}
	if (map->valid != VALID)
		return (-1);
	free(line);
	close(fd);
	return (1);
}

//Checks if the file extension is .cub
//Returns -1 on error
int	check_end(char *str, char *end)
{
	int	len;
	int	elen;

	len = ft_strlen(str);
	elen = ft_strlen(end);
	if (len <= elen)
		return (-1);
	while (--len >= 0 && --elen >= 0)
	{
		if (str[len] != end[elen])
			return (-1);
	}
	return (0);
}

//Adds a line to the map
//Returns -1 on malloc failure
//Returns number of lines on success
static int	map_add_line(t_map *map, char *line)
{
	char	**new_map;
	int		i;

	i = 0;
	while (map->map[i])
		i++;
	new_map = malloc(sizeof(char *) * (i + 2));
	if (!new_map)
		return (-1);
	i = -1;
	while (map->map[++i])
		new_map[i] = map->map[i];
	new_map[i++] = ft_strdup(line);
	new_map[i] = NULL;
	free(map->map);
	map->map = new_map;
	return (i);
}

static void	set_door(char **map, int y, int x, t_door *door)
{
	door->x = x;
	door->y = y;
	door->open = 0;
	if (map[y + 1][x] == '1' && map[y - 1][x] == '1')
		door->direction = 'Y';
	else if (map[y][x + 1] == '1' && map[y][x - 1] == '1')
		door->direction = 'X';
}

//Adds a door index terminating it with a -1 -1 vector
//Returns error if malloc fails
int	add_door(t_map *map, int y, int x)
{
	t_door	*new_doors;
	int		i;

	i = 0;
	while (map->doors && map->doors[i].x != -1)
		i++;
	new_doors = malloc(sizeof(t_door) * (i + 2));
	if (!new_doors)
		return (invalidate_map(map, MALLOC));
	i = 0;
	while (map->doors && map->doors[i].x != -1)
	{
		new_doors[i] = map->doors[i];
		i++;
	}
	set_door(map->map, y, x, &new_doors[i++]);
	new_doors[i].x = -1;
	free(map->doors);
	map->doors = new_doors;
	return (0);
}

int	index_doors(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map->map[++i])
	{
		while (map->map[i][++j])
		{
			if (map->map[i][j] == 'D')
			{
				if (add_door(map, i, j) != 0)
					return (invalidate_map(map, MALLOC));
				map->map[i][j] = '1';
			}
		}
		j = -1;
	}
	return (0);
}

int	parser(int argc, char **argv, t_map *map)
{
	if (argc != 2)
		return (parse_error(NULL, "Wrong amount of arguments\n"));
	if (check_end(argv[1], ".cub") == -1)
		return (parse_error(NULL, "Map file must end with .cub\n"));
	init_map(map);
	if (read_map(map, argv) == -1)
		return (parse_error(map, NULL));
	if (check_map(map) == -1)
		return (parse_error(map, NULL));
	if (index_doors(map) == -1)
		return (parse_error(map, NULL));
	print_map(*map);
	return (0);
}
