/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:04:46 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/15 05:05:35 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_data(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	data->ts = 64;
	data->ps = 16;
	data->p_img = mlx_new_image(data->mlx, 16, 16);
	if (data->p_img == NULL)
		return (ERROR_MALLOC);
	ft_memset(data->p_img->pixels, 255,
		data->p_img->width * data->p_img->height * sizeof(int));
	data->speed = WALK;
	return (0);
}

void	copy_map(t_data *data, t_map *map)
{
	data->map = map->map;
	map->map = NULL;
	data->map_ = map;
	data->angle = data->map_->position * M_PI_2;
	data->d_x = cos(data->angle);
	data->d_y = sin(data->angle);
	data->p_x = map->pos_x * data->ts + data->ps / 2;
	data->p_y = map->pos_y * data->ts + data->ps / 2;
	mlx_set_window_size(data->mlx, map->width * data->ts,
		map->height * data->ts);
}

int	init_walls(t_data *data)
{
	mlx_image_t	*walls;

	walls = mlx_new_image(data->mlx, 64, 64);
	if (walls == NULL)
		return (ERROR_MALLOC);
	ft_memset(walls->pixels, 180, walls->width * walls->height * sizeof(int));
	data->walls = walls;
	return (0);
}

int	init_rays(t_data *data, t_map *map)
{
	float	x;
	float	y;

	x = data->p_x;
	y = data->p_y;
	// printf("%i %i\n", map->width, map->height);
	// exit(0);
	data->rays = mlx_new_image(data->mlx, map->width * data->ts, map->height * data->ts);
	if (data->rays == NULL)
		return (ERROR_MALLOC);
	// ft_memset(data->rays->pixels, 110,
	// 	map->width * data->ts * map->height * data->ts * sizeof(int));
	// for (int i = 0; i < 100; i++)
	// {
	// 	if ((x > 0 && x < data->map_->width * data->ts)
	// 		&& (y > 0 && y < data->map_->height * data->ts))
	// 		mlx_put_pixel(data->rays, x, y, 0x00FF00FF);
	// 	x = x + data->d_x * i * 0.1;
	// 	y = y + data->d_y * i * 0.1;
	// }
	mlx_image_to_window(data->mlx, data->rays, 0, 0);
	return (0);
}

int	init(t_data *data, t_map *map)
{
	if (init_data(data) != 0)
		return (1);
	copy_map(data, map);
	if (init_walls(data) != 0)
		return (2);
	if (init_rays(data, map) != 0)
		return (3);
	return (0);
}
