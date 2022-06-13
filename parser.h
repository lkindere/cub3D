/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:34:24 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/13 14:38:57 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <sys/errno.h>

# include <stdio.h>

typedef enum e_errors
{
	VALID,
	INVALID_ARGS,
	INVALID_MAP_FORMAT,
	INVALID_PATH_FORMAT,
	INVALID_COLOR_FORMAT,
	DUPLICATE_DEFINITION,
	UNCLOSED_MAP,
	NO_MAP,
	MALLOC
}	t_errors;

typedef enum e_pos
{
	NONE,
	N,
	S,
	E,
	W
}	t_pos;

typedef struct s_map
{
	char			**map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				floor_color;
	int				ceiling_color;
	unsigned int	width;
	unsigned int	height;
	enum e_pos		position;
	enum e_errors	valid;
}	t_map;

int		parser(int argc, char **argv);

//Init
void	init_map(t_map *map);
void	free_map(t_map *map);

//Get
int		get_textures(t_map *map, char *line);
int		get_colors(t_map *map, char *line);
int		get_map(t_map *map, char *line);

//Check
int		check_map(t_map *map);
int		check_walls(t_map *map);

//Utils
void	print_map(t_map map);
int		invalidate_map(t_map *map, enum e_errors err);
int		get_line(int fd, char **line);
int		check_empty(char *line);

//Helpers
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_join_free(char const *s1, char const *s2, int sfree);
int		ft_atoi(const char *str);
int		ft_isspace(int c);
int		ft_isdigit(int c);

#endif