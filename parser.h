/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:34:24 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/12 20:29:26 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <sys/errno.h>

#include <stdio.h>

typedef enum e_errors
{
	VALID,
	INVALID_ARGS,
	INVALID_FORMAT,
	DUPLICATE_DEFINITION,
} t_errors;

typedef struct s_map
{
	char			**map;
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	int				floor_color;
	int				ceiling_color;
	int				width;
	int				height;
	enum e_errors	valid;
} t_map;

int		parser(int argc, char **argv);

//Init
void	init_map(t_map *map);

//Textures
int		check_textures(t_map *map, char *line);

//Colors
int		check_colors(t_map *map, char *line);

//Utils
void	print_map(t_map map);
int		invalidate_map(t_map *map, enum e_errors err);
int		get_line(int fd, char **line);
int		check_empty(char *line);

//Helpers
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_join_free(char const *s1, char const *s2, int sfree);
int		ft_atoi(const char *str);
int		ft_isspace(int c);
int		ft_isdigit(int c);


#endif