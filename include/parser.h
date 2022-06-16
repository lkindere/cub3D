/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:34:24 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/16 14:22:08 by lkindere         ###   ########.fr       */
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
# include <limits.h>

# include "map.h"

int		parser(int argc, char **argv, t_map *map);

//Init
void	init_map(t_map *map);
int		free_map(t_map *map);
int		parse_error(t_map *map, char *str);

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
int		is_block(char c);

#endif