/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:18:21 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/21 18:11:55 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reset_background(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < data->draw->height / 2)
	{
		while (++j < data->draw->width)
			mlx_put_pixel(data->draw, j, i, data->map_->ceiling_color);
		j = -1;
	}
	while (i < data->draw->height)
	{
		while (++j < data->draw->width)
			mlx_put_pixel(data->draw, j, i, data->map_->floor_color);
		j = -1;
		i++;
	}
}

void	reset_images(t_data *data)
{
	ft_memset(data->rays->pixels, 0,
		data->rays->width * data->rays->height * sizeof(int));
	reset_background(data);
	data->p_img->instances[0].x = (data->player.x - PS / 2) * data->tsm;
	data->p_img->instances[0].y = (data->player.y - PS / 2) * data->tsm;
}

void	hook(void *param)
{
	uint32_t	color;
	uint8_t		rgba[4];
	t_data		*data;

	data = param;
	player_speed(data);
	player_rotate(data);
	data->angle = angle_fit(data->angle);
	reset_images(data);
	raycaster(data);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_R)
		data->player = vector(2.5, 2.5);
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		player_dash(data);
}
