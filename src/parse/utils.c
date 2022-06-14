/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:22:22 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/14 21:54:01 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <string.h>

//Sets map valid to enum
//Returns -1
int	invalidate_map(t_map *map, enum e_errors err)
{
	if (map->valid == VALID)
		map->valid = err;
	return (-1);
}


//Checks if map block is a valid identifier
//Spaces and null are considered valid
int	is_block(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S'
		&& c != 'W' && c != 'E' && c != 0 && c != ' ')
		return (0);
	return (1);
}

void	print_map(t_map map)
{
	printf("NO: %s\n", map.no);
	printf("SP: %s\n", map.so);
	printf("WE: %s\n", map.we);
	printf("EA: %s\n", map.ea);
	printf("Floor: %d\n", map.floor_color);
	printf("R: %d, G: %d, B: %d\n\n",
		(unsigned int)map.floor_color >> 16,
		(unsigned int)(map.floor_color << 16) >> 24,
		(unsigned int)(map.floor_color << 24) >> 24);
	printf("Ceiling: %d\n", map.ceiling_color);
	printf("R: %d, G: %d, B: %d\n\n",
		(unsigned int)map.ceiling_color >> 16,
		(unsigned int)(map.ceiling_color << 16) >> 24,
		(unsigned int)(map.ceiling_color << 24) >> 24);
	printf("Valid: %d\n", map.valid);
	printf("\nMap:\n");
	if (map.map)
		for (int i = 0; map.map[i]; i++)
			printf("%s\n", map.map[i]);
	printf("\nHeight: %d\n", map.height);
	printf("Width: %d\n\n", map.width);
	printf("Starting pos: %d\n", map.position);
	printf("Starting X: %d, Y:%d\n", map.pos_x, map.pos_y);
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
	errno = 0;
	while (read(fd, buffer, 1) > 0)
	{
		if (buffer[0] == 0 && write(2, "Go away code breaker!\n", 23))
			exit(1);
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
