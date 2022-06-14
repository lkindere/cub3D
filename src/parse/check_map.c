/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:17:26 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/14 18:13:40 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Stretches all lines to max width
//Returns -1 on malloc failure
//Returns 1 on success
static int	stretch_width(t_map *map)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (map->map[++i])
	{
		if (ft_strlen(map->map[i]) != map->width)
		{
			temp = malloc(map->width + 1);
			if (!temp)
				return (invalidate_map(map, MALLOC));
			while (map->map[i][++j])
				temp[j] = map->map[i][j];
			while (j < (int)map->width)
				temp[j++] = ' ';
			temp[j] = 0;
			free(map->map[i]);
			map->map[i] = temp;
			temp = NULL;
			j = -1;
		}
	}
	return (1);
}

//Returns -1 on invalid dimensions
//Returns 1 on valid
//Removes \n on end of lines
//Sets starting position
static int	width_height(t_map *map)
{
	int	i;
	int	len;
	int	width;

	i = -1;
	len = 0;
	width = 0;
	while (map->map[++i])
	{
		while (map->map[i][len] && map->map[i][len] != '\n')
			len++;
		if (map->map[i][len] == '\n')
			map->map[i][len] = 0;
		if (len > width)
			width = len;
		len = 0;
	}
	if (i < 3 || width < 3)
		return (invalidate_map(map, INVALID_MAP_FORMAT));
	map->height = i;
	map->width = width;
	return (1);
}

//Sets position to enum
//Returns -1 on invalid
//Returns 1 on valid
static int	try_set_pos(t_map *map, char pos)
{
	if (map->position != NO_POS)
		return (invalidate_map(map, DUPLICATE_DEFINITION));
	if (pos == 'N')
	{
		map->position = N;
		return (1);
	}
	if (pos == 'S')
	{
		map->position = S;
		return (1);
	}
	if (pos == 'E')
	{
		map->position = E;
		return (1);
	}
	if (pos == 'W')
		map->position = W;
	return (1);
}

//Checks for starting position
//Returns -1 on invalid
//Returns 1 on valid
static int	check_pos(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map->map[++i])
	{
		while (map->map[i][++j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				if (try_set_pos(map, map->map[i][j]) == -1)
					return (invalidate_map(map, DUPLICATE_DEFINITION));
				map->pos_x = j;
				map->pos_y = i;
			}
		}
		j = -1;
	}
	if (map->position == NO_POS)
		return (invalidate_map(map, INVALID_MAP_FORMAT));
	return (1);
}

//Returns 1 on valid map
//Returns -1 on invalid map
int	check_map(t_map *map)
{
	if (check_pos(map) == -1)
		return (invalidate_map(map, INVALID_MAP_FORMAT));
	if (width_height(map) == -1)
		return (invalidate_map(map, INVALID_MAP_FORMAT));
	if (stretch_width(map) == -1)
		return (invalidate_map(map, MALLOC));
	if (check_walls(map) == -1)
		return (invalidate_map(map, UNCLOSED_MAP));
	return (1);
}
