/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:24:54 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/23 08:40:57 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Returns 1 on valid texture
//Returns -1 on invalid
static int	try_set_texture(t_map *map, char **texture, char *line)
{
	int	i;

	if (*texture != NULL)
		return (invalidate_map(map, DUPLICATE_DEFINITION));
	while (ft_isspace(*line))
		line++;
	if (!*line)
		return (invalidate_map(map, INVALID_PATH_FORMAT));
	(*texture) = ft_strdup(line);
	i = ft_strlen(*texture);
	while (--i > 0 && ft_isspace((*texture)[i]))
		(*texture)[i] = 0;
	if (!(*texture))
		return (invalidate_map(map, MALLOC));
	return (1);
}

static int	add_door_texture(t_map *map, char ***texture, char *line)
{
	int		i;
	char	**new_textures;

	i = 0;
	while (*texture && (*texture)[i])
		i++;
	new_textures = malloc(sizeof(char *) * (i + 2));
	if (!new_textures)
		return (invalidate_map(map, MALLOC));
	i = 0;
	while (*texture && (*texture)[i])
	{
		new_textures[i] = (*texture)[i];
		i++;
	}
	new_textures[i] = ft_strdup(line);
	if (!new_textures[i++])
		return (invalidate_map(map, MALLOC));
	new_textures[i] = NULL;
	free (*texture);
	(*texture) = new_textures;
	return (1);
}

static int	try_set_door(t_map *map, char ***texture, char *line)
{
	int		i;

	i = 0;
	while (ft_isspace(*line))
		line++;
	if (!*line)
		return (invalidate_map(map, INVALID_PATH_FORMAT));
	i = ft_strlen(line);
	while (--i > 0 && ft_isspace(line[i]))
		line[i] = 0;
	return (add_door_texture(map, texture, line));
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
	if (!ft_strncmp("DOOR ", line, 3))
		return (try_set_door(map, &map->door_text, &line[5]));
	return (0);
}
