/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:24:54 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/12 20:27:07 by lkindere         ###   ########.fr       */
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
	printf("%s\n", &line[i + 1]);
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
	// printf("Checking texture\n");
	if (*texture != NULL)
		return (invalidate_map(map, DUPLICATE_DEFINITION));
	// printf("Pass\n");
	if (space_check(line) != 0)
		return (invalidate_map(map, INVALID_FORMAT));
	// printf("Space pass\n");
	(*texture) = line;
	return (1);
}

//Returns 1 on valid texture
//Returns 0	if not a texture
//Returns -1 on error
int	check_textures(t_map *map, char *line)
{
	if (!ft_strncmp("NO ", line, 3))
		return (try_set_texture(map, &map->NO, &line[3]));
	if (!ft_strncmp("SO ", line, 3))
		return (try_set_texture(map, &map->SO, &line[3]));
	if (!ft_strncmp("WE ", line, 3))
		return (try_set_texture(map, &map->WE, &line[3]));
	if (!ft_strncmp("EA ", line, 3))
		return (try_set_texture(map, &map->EA, &line[3]));
	return (0);
}
