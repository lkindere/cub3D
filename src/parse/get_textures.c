/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:24:54 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/14 19:20:33 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Returns 1 if a whitespace is found
//Returns 1 if path is empty
//Ignores newline at end of line;
//Returns 0 if no whitespace
static int	space_check(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			return (1);
		if (line[i] >= 11 && line[i] <= 13)
			return (1);
		if (line[i] == '\n' && line[i + 1])
			return (1);
	}
	if (i < 1)
		return (1);
	return (0);
}	

//Returns 1 on valid texture
//Returns -1 on invalid
static int	try_set_texture(t_map *map, char **texture, char *line)
{
	if (*texture != NULL)
		return (invalidate_map(map, DUPLICATE_DEFINITION));
	while (ft_isspace(*line))
		line++;
	if (space_check(line) != 0)
		return (invalidate_map(map, INVALID_PATH_FORMAT));
	(*texture) = ft_strdup(line);
	if (!(*texture))
		return (invalidate_map(map, MALLOC));
	return (1);
}

//Returns 1 on valid texture
//Returns 0	if not a texture
//Returns -1 on error
int	get_textures(t_map *map, char *line)
{
	while (ft_isspace(*line))
		line++;
	if (!ft_strncmp("NO ", line, 3))
		return (try_set_texture(map, &map->no, &line[3]));
	if (!ft_strncmp("SO ", line, 3))
		return (try_set_texture(map, &map->so, &line[3]));
	if (!ft_strncmp("WE ", line, 3))
		return (try_set_texture(map, &map->we, &line[3]));
	if (!ft_strncmp("EA ", line, 3))
		return (try_set_texture(map, &map->ea, &line[3]));
	return (0);
}
