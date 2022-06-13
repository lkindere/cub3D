/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:17:26 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/13 14:43:27 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		if (map->map[0][i] != '1' && map->map[0][i] != ' ')
			return (-1);
	}
	i = -1;
	while (map->map[h][++i])
	{
		if (map->map[h][i] != '1' && map->map[h][i] != ' ')
			return (-1);
	}
	return (1);
}

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
		return (-1);
	map->height = i;
	map->width = width;
	return (1);
}

//Returns 1 on valid map
//Returns -1 on invalid map
int	check_map(t_map *map)
{
	if (width_height(map) == -1)
		return (invalidate_map(map, INVALID_MAP_FORMAT));
	if (stretch_width(map) == -1)
		return (invalidate_map(map, MALLOC));
	if (top_bottom(map) == -1)
		return (invalidate_map(map, INVALID_MAP_FORMAT));
	if (check_walls(map) == -1)
		return (invalidate_map(map, UNCLOSED_MAP));
	return (1);
}
