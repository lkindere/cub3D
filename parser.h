/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:34:24 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/12 19:45:47 by lkindere         ###   ########.fr       */
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

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_join_free(char const *s1, char const *s2, int sfree);

int		ft_atoi(const char *str);

int		ft_isspace(int c);
int		ft_isdigit(int c);


#endif