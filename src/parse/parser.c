/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:34:16 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/23 16:16:11 by lkindere         ###   ########.fr       */
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
	// print_map(*map);
	return (0);
}
