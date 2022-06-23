/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:25:22 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/23 15:55:35 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Returns 1 on valid colors
//Returns -1 on invalid
static int	valid_format(char *line)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	while (line[i] && (ft_isdigit(line[i]) || line[i] == ','))
	{
		while (ft_isdigit(line[i]))
			i++;
		if (i < 1 || i > 3 || (n < 3 && line[i] != ','))
			return (-1);
		line = &line[i + 1];
		i = 0;
		n++;
	}
	if (n != 4)
		return (-1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (-1);
		i++;
	}
	return (1);
}

//Returns 1 on valid color
//Returns -1 on invalid
static int	try_set_color(t_map *map, long *color, char *line)
{
	int				i;
	int				c;
	unsigned int	rgb[3];

	i = 0;
	c = 0;
	if ((*color) != -1)
		return (invalidate_map(map, DUPLICATE_DEFINITION));
	while (ft_isspace(*line))
		line++;
	if (valid_format(line) == -1)
		return (invalidate_map(map, INVALID_COLOR_FORMAT));
	while (c < 3)
	{
		rgb[c++] = ft_atoi(line);
		while (ft_isdigit(line[i]))
			i++;
		line = &line[i + 1];
		i = 0;
	}
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (invalidate_map(map, INVALID_COLOR_FORMAT));
	*color = ((rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + 255);
	return (1);
}

//Returns 1 on valid color
//Returns 0 if not a color
//Returns -1 on error
int	get_colors(t_map *map, char *line)
{	
	while (ft_isspace(*line))
		line++;
	if (!ft_strncmp("F ", line, 2))
		return (try_set_color(map, &map->floor_color, &line[2]));
	if (!ft_strncmp("C ", line, 2))
		return (try_set_color(map, &map->ceiling_color, &line[2]));
	return (0);
}
