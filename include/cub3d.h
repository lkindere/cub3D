/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 00:47:44 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/20 01:43:20 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include "math_utils.h"
# include "map.h"
# include "math_utils.h"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <fcntl.h>

# define WIDTH 920
# define HEIGHT 480

//Map: 		int representation of starting tile
//Start: 	Starting x and y
//Dir:		Starting direction
//Len:		Length in x or y
//Step:		Unit step size in x or y
//Hit:		Wall hit x and y
//Distance:	Distance to wall hit
typedef struct s_ray
{
	t_vec_int	map;
	t_vec		start;
	t_vec		dir;
	t_vec		len;
	t_vec		step;
	t_vec		hit;
	float		distance;
}	t_ray;

typedef enum s_error
{
	NONE,
	ERROR_GENERAL,
	ERROR_MALLOC
}	t_error;

typedef enum s_speed
{
	WALK = 2,
	SPRINT = 3,
	SNEAK = 1,
	DASH = 20
}	t_speed;

typedef struct s_textures
{
	xpm_t	*n;
	xpm_t	*s;
	xpm_t	*e;
	xpm_t	*w;
}	t_textures;

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
	float		ps;
	mlx_t		*mlx;
	mlx_image_t	*p_img;
	float		speed;
	float		angle;
	float		d_x;
	float		d_y;
	float		p_x;
	float		p_y;
	mlx_image_t	*walls;
	t_map		*map_;
	mlx_image_t	*rays;
	t_textures	textures;
}	t_data;

/*	hook				*/

void		hook(void *param);
void		key_hook(mlx_key_data_t keydata, void *param);
t_ray		do_rays(t_data *data, t_vec start, t_vec dir, float range);

/*	inits				*/

int			init(t_data *data, t_map *map);

/*	player				*/
float		angle_fit(float angle);
void		player_rotate(t_data *data);
void		player_move(t_data *data);
int			check_collision(t_data *data, float x, float y);
void		player_dash(t_data *data);
void		player_speed(t_data *data);


/*	utils				*/

int			ft_add_char(char **str, char c);
int			ft_add_str(char **str, char *add);



t_vec_int	screen_bounds(int x, int y);

void	safe_pixel(mlx_image_t *image, t_vec vec, uint32_t color);
void	draw_line(mlx_image_t *image, t_vec p1, t_vec p2, uint32_t color);

#endif
