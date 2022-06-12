/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:34:16 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/12 20:25:37 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Returns 1 on valid line
//Returns 0 on empty line
//Returns -1 on error
int	check_line(t_map *map, char *line)
{
	if (check_empty(line) == 1)
		return (0);
	if (check_textures(map, line) == 1)
		return (1);
	if (map->valid != VALID)
		return (-1);
	if (check_colors(map, line) == 1)
		return (1);
	if (map->valid != VALID)
		return (-1);
	return (0);
}

//Returns 1 on valid map
//Returns -1 on invalid map
int	get_map(t_map *map, char **argv)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		; // Error open can exit
	while (get_line(fd, &line) > 0)
	{
		if (check_line(map, line) <= 0)
			free(line);
		line = NULL;
		if (map->valid != VALID)
			return (-1);
	}
	return (1);
}

int	parser(int argc, char **argv)
{
	t_map	map;

	printf("Argc: %d\n", argc);
	if (argc != 2)
		; //Error invalid argument
	init_map(&map);
	get_map(&map, argv);

	print_map(map);
	
	return (0);
}
