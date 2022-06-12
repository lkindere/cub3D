/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:22:22 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/12 20:24:10 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Sets map valid to enum
//Returns -1
int	invalidate_map(t_map *map, enum e_errors err)
{
	map->valid = err;
	return (-1);
}

void	print_map(t_map map)
{
	printf("NO: %s\n", map.NO);
	printf("SP: %s\n", map.SO);
	printf("WE: %s\n", map.WE);
	printf("EA: %s\n", map.EA);
	printf("Floor: %d\n", map.floor_color);
	printf("R: %d, G: %d, B: %d\n", 
		(unsigned int)map.floor_color >> 16, 
		(unsigned int)(map.floor_color << 16) >> 24, 
		(unsigned int)(map.floor_color << 24) >> 24);
	printf("Ceiling: %d\n", map.ceiling_color);
	printf("R: %d, G: %d, B: %d\n", 
		(unsigned int)map.ceiling_color >> 16, 
		(unsigned int)(map.ceiling_color << 16) >> 24, 
		(unsigned int)(map.ceiling_color << 24) >> 24);
	printf("Valid: %d\n", map.valid);
}

//Returns 1 if line is empty
//Returns 0 if not
int	check_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

//Returns line length on successful read
//Returns -1 on error
int	get_line(int fd, char **line)
{
	int		len;
	char	buffer[2];

	len = 0;
	buffer[1] = 0;
	while (read(fd, buffer, 1) > 0)
	{
		len++;
		*line = ft_join_free(*line, buffer, 1);
		if (!(*line))
			return (-1);
		if ((*line)[len - 1] == '\n')
			break ;
	}
	if (errno != 0)
	{
		free((*line));
		(*line) = NULL;
		return (-1);
	}
	return (len);
}
