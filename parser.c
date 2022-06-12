/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:34:16 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/12 20:13:05 by lkindere         ###   ########.fr       */
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


//Returns 1 if a whitespace is found
//Returns 1 if path is empty
//Ignores newline at end of line;
//Returns 0 if no whitespace
int	space_check(char *line)
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
int	try_set_texture(t_map *map, char **texture, char *line)
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


//Returns 1 on valid colors
//Returns -1 on invalid
int	color_check(char *line)
{
	int	i;
	int	n;
	
	i = 0;
	n = 1;
	while (line[i] && (ft_isdigit(line[i]) || line[i] == ','))
	{
		while (ft_isdigit(line[i]))
			i++;
		if (i < 1 || i > 3)
			return (-1);
		if (n < 3 && line[i] != ',')
			return (-1);
		line = &line[i + 1];
		i = 0;
		n++;
	}
	if (n != 4 || line[i] != 0)
		return (-1);
	return (1);
}

//Returns 1 on valid color
//Returns -1 on invalid
int	try_set_color(t_map *map, int *color, char *line)
{
	int	i;
	int	c;
	int	RGB[3];

	i = 0;
	c = 0;
	if (color_check(line) == -1)
	{
		map->valid = INVALID_FORMAT;
		return (-1);
	}
	while (c < 3)
	{
		RGB[c++] = ft_atoi(line);
		while (ft_isdigit(line[i]))
			i++;
		line = &line[i + 1];
		i = 0;
	}
	if (RGB[0] > 255 || RGB[1] > 255 || RGB[2] > 255)
		invalidate_map(map, INVALID_FORMAT);
	*color = ((RGB[0] << 16) + (RGB[1] << 8) + RGB[2]);
	return (1);
}

//Returns 1 on valid color
//Returns 0 if not a color
//Returns -1 on error
int	check_colors(t_map *map, char *line)
{
	if (!ft_strncmp("F ", line, 2))
		try_set_color(map, &map->floor_color, &line[2]);
	if (!ft_strncmp("C ", line, 2))
		try_set_color(map, &map->ceiling_color, &line[2]);
	return (0);
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

//Returns 1 on valid line
//Returns 0 on empty line
//Returns -1 on error
int	check_line(t_map *map, char *line)
{
	if (check_empty(line) == 1)
		return (0);
	if (check_textures(map, line) == 1)
		return (1);
	if (map->valid != VALID)
		return (-1);
	if (check_colors(map, line) == 1)
		return (1);
	if (map->valid != VALID)
		return (-1);
	return (0);
}


//Returns 1 on valid map
//Returns -1 on invalid map
int	get_map(t_map *map, char **argv)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		; // Error open can exit
	while (get_line(fd, &line) > 0)
	{
		if (check_line(map, line) <= 0)
			free(line);
		line = NULL;
		if (map->valid != VALID)
			return (-1);
	}
	return (1);
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->NO = NULL;
	map->SO = NULL;
	map->WE = NULL;
	map->EA = NULL;
	map->floor_color = 0;
	map->ceiling_color = 0;
	map->width = 0;
	map->height = 0;
	map->valid = VALID;
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

int	parser(int argc, char **argv)
{
	t_map	map;

	printf("Argc: %d\n", argc);
	if (argc != 2)
		; //Error invalid argument
	init_map(&map);
	get_map(&map, argv);

	print_map(map);
	
	return (0);
}
