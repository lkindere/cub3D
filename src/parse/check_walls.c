/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:23:00 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/14 21:52:54 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Returns -1 no wall left
//Returns -2 no wall right
//Returns -3 no wall top
//Returns -4 no wall bottom
//Returns -5 no wall top left
//Returns -6 no wall top right
//Returns -7 no wall bottom left
//Returns -8 no wall botom right
//Returns 1 on surrounded wall
static int	is_surrounded(t_map *map, int h, int w)
{
	if (w == 0 || map->map[h][w - 1] == ' ')
		return (-1);
	if (map->map[h][w + 1] == ' ' || map->map[h][w + 1] == 0)
		return (-2);
	if (map->map[h - 1][w] == ' ')
		return (-3);
	if (map->map[h + 1][w] == ' ' || map->map[h + 1][w] == 0)
		return (-4);
	if (map->map[h - 1][w - 1] == ' ')
		return (-5);
	if (map->map[h - 1][w + 1] == ' ' || map->map[h - 1][w + 1] == 0)
		return (-6);
	if (map->map[h + 1][w - 1] == ' ')
		return (-7);
	if (map->map[h + 1][w + 1] == ' ' || map->map[h + 1][w + 1] == 0)
		return (-8);
	return (1);
}

//Checks if top and bottom are only walls and spaces
//Returns -1 on invalid
//Returns 1 on valid
static int	top_bottom(t_map *map)
{
	int	i;
	int	h;

	i = -1;
	h = map->height - 1;
	while (map->map[0][++i])
	{
		if (!is_block(map->map[0][i]))
			return (invalidate_map(map, INVALID_MAP_FORMAT));
		if (map->map[0][i] != '1' && map->map[0][i] != ' ')
			return (invalidate_map(map, UNCLOSED_MAP));
	}
	i = -1;
	while (map->map[h][++i])
	{
		if (!is_block(map->map[0][i]))
			return (invalidate_map(map, INVALID_MAP_FORMAT));
		if (map->map[h][i] != '1' && map->map[h][i] != ' ')
			return (invalidate_map(map, UNCLOSED_MAP));
	}
	return (1);
}

//Checks if the middle is surrounded by walls
//Returns 1 on valid top/bottom
//Returns -1 on invalid
int	check_walls(t_map *map)
{
	int	h;
	int	w;

	h = 0;
	w = -1;
	if (top_bottom(map) == -1)
		return (invalidate_map(map, UNCLOSED_MAP));
	while (map->map[++h] && map->map[h + 1])
	{
		while (map->map[h][++w])
		{
			while (map->map[h][w] == ' ')
				w++;
			if (!is_block(map->map[h][w]))
				return (invalidate_map(map, INVALID_MAP_FORMAT));
			if (!map->map[h][w])
				break ;
			if (map->map[h][w] != '1' && is_surrounded(map, h, w) < 0)
				return (invalidate_map(map, UNCLOSED_MAP));
		}
		w = -1;
	}
	return (1);
}
