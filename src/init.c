/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:04:46 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/15 02:06:18 by mmeising         ###   ########.fr       */
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

int	copy_map(t_data *data, t_map *map)
{
	data->map = map->map;
	map->map = NULL;
	data->map_ = map;
	data->angle = data->map_->position * M_PI_2;
	data->p_x = map->pos_x * data->ts + data->ps / 2;
	data->p_y = map->pos_y * data->ts + data->ps / 2;
	mlx_set_window_size(data->mlx, data->map_->width * data->ts, data->map_->height * data->ts);
	return (0);
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

int	init(t_data *data, t_map *map)
{
	if (init_data(data) != 0)
		return (1);
	if (copy_map(data, map) != 0)
		return (2);
	if (init_walls(data) != 0)
		return (3);
	return (0);
}
