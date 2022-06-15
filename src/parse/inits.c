/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:23:47 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/15 03:46:40 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_error(t_map *map, char *str)
{
	if (str && write(2, str, ft_strlen(str)))
		return (-1);
	else if (map->valid == INVALID_ARGS)
		write(2, "Invalid arguments provided", 27);
	else if (map->valid == INVALID_MAP_FORMAT)
		write(2, "Invalid map format", 19);
	else if (map->valid == INVALID_PATH_FORMAT)
		write(2, "Invalid path format", 20);
	else if (map->valid == INVALID_COLOR_FORMAT)
		write(2, "Invalid color format", 21);
	else if (map->valid == DUPLICATE_DEFINITION)
		write(2, "Duplicate definitions in map file", 34);
	else if (map->valid == UNCLOSED_MAP)
		write(2, "Map is not closed off", 22);
	else if (map->valid == NO_MAP)
		write(2, "No map provided", 16);
	else if (map->valid == MALLOC)
		write(2, "Malloc failed", 14);
	write (2, "\n", 1);
	return (free_map(map));
}

int	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return (-1);
	while (map->map && map->map[i])
		free(map->map[i++]);
	free(map->map);
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	return (-1);
}

void	init_map(t_map *map)
{
	map->map = malloc(sizeof(char *));
	if (!map->map)
		exit (0);
	map->map[0] = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->width = 0;
	map->height = 0;
	map->pos_x = 0;
	map->pos_y = 0;
	map->position = NO_POS;
	map->valid = VALID;
}
