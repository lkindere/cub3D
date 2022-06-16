/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 00:47:44 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/16 12:21:27 by lkindere         ###   ########.fr       */
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
	SNEAK = 3,
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
	int			speed;
	float		angle;
	float		d_x;
	float		d_y;
	float		p_x;
	float		p_y;
	mlx_image_t	*walls;
	t_map		*map_;
	mlx_image_t	*rays;
}	t_data;

/*	hook				*/

void		hook(void *param);
void		key_hook(mlx_key_data_t keydata, void *param);

/*	inits				*/

int			init(t_data *data, t_map *map);

/*	player				*/
float		angle_fit(float angle);
void		player_rotate(t_data *data);
void		player_move(t_data *data);
int			check_collision(t_data *data, float x, float y);
void		player_dash(t_data *data);
void		player_speed(t_data *data);

void		do_rays(t_data *data);

/*	utils				*/

int			ft_add_char(char **str, char c);
int			ft_add_str(char **str, char *add);

#endif
