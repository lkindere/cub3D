/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:19:30 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/22 14:39:43 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "math_utils.h"

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
	E = 0,
	S = 1,
	W = 2,
	N = 3,
	D = 4,
	NO_POS
}	t_pos;

typedef struct s_map
{
	char			**map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	unsigned int	width;
	unsigned int	height;
	unsigned int	pos_x;
	unsigned int	pos_y;
	enum e_pos		position;
	enum e_errors	valid;
	t_vec_int		*door_indexes;
}	t_map;

int		parser(int argc, char **argv, t_map *map);

#endif