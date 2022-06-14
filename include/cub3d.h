/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 00:47:44 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/15 01:03:03 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include "math_utils.h"
# include "parser.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <fcntl.h>

# define WIDTH 920
# define HEIGHT 480

typedef enum s_error
{
	NONE,
	ERROR_GENERAL,
	ERROR_MALLOC
}	t_error;

typedef enum s_speed
{
	WALK = 5,
	SPRINT = 10,
	SNEAK = 1,
	DASH = 96
}	t_speed;

/**
 *	@param input_path Path to input map file.
 *	@param map Array of strings with map content.
 *	@param ts Tile size.
 *	@param ps Player size.
 *	@param mlx Main mlx handle.
 *	@param player Player struct carrying important data for the player.
 *	@param walls Walls struct to be rendered.
 */
typedef struct s_data
{
	char		*input_path;
	char		**map;
	int			ts;
	int			ps;
	mlx_t		*mlx;
	mlx_image_t	*p_img;
	mlx_image_t	*crosshair;
	int			speed;
	float		angle;
	float		d_x;
	float		d_y;
	float		p_x;
	float		p_y;
	mlx_image_t	*walls;
	t_map		*map_;
}	t_data;

/*	hook				*/

void		hook(void *param);
void		key_hook(mlx_key_data_t keydata, void *param);

/*	inits				*/

int			init(t_data *data, t_map *map);

/*	player				*/

void		player_move(t_data *data);
void		player_dash(t_data *data);
void		player_rotate(t_data *data);
void		move_up(t_data *data, int step);
void		move_down(t_data *data, int step);
void		move_left(t_data *data, int step);
void		move_right(t_data *data, int step);

void		player_speed(t_data *data);

int			collision(t_data *data, int32_t x, int32_t y, char **map);

/*	utils				*/

int			ft_add_char(char **str, char c);
int			ft_add_str(char **str, char *add);

#endif
