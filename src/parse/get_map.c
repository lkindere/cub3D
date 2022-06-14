/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:20:55 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/13 14:24:48 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

//Returns 1 if valid map line
//Returns 0 if not
//Returns -1 on malloc failure
int	get_map(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '1' || line[i] == '0'
		|| line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'E' || line[i] == 'W')
		return (map_add_line(map, line));
	return (0);
}
