/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:25:56 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/23 13:27:24 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
static int	add_door(t_map *map, int y, int x)
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
	if (map->doors && !map->door_text)
		return (invalidate_map(map, INVALID_DOORS));
	return (0);
}
