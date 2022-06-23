/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:18:21 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/23 15:46:13 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reset_background(t_data *data, uint32_t ceiling, uint32_t floor)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < data->draw->height / 2)
	{
		while (data->effects & 4 && j < data->draw->width)
			mlx_put_pixel(data->draw, j++, i, funky_stuff(ceiling));
		while (j < data->draw->width)
			mlx_put_pixel(data->draw, j++, i, ceiling);
		j = 0;
		i++;
	}
	while (i < data->draw->height)
	{
		while (data->effects & 8 && j < data->draw->width)
			mlx_put_pixel(data->draw, j++, i, funky_stuff(floor));
		while (j < data->draw->width)
			mlx_put_pixel(data->draw, j++, i, floor);
		j = 0;
		i++;
	}
}

void	reset_images(t_data *data)
{
	ft_memset(data->rays->pixels, 0,
		data->rays->width * data->rays->height * sizeof(int));
	reset_background(data, data->map_->ceiling_color, data->map_->floor_color);
	data->p_img->instances[0].x = (data->player.x - PS / 2) * data->tsm;
	data->p_img->instances[0].y = (data->player.y - PS / 2) * data->tsm;
}

void	hook(void *param)
{
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
	if (keydata.key == MLX_KEY_G && keydata.action == MLX_PRESS)
		open_door(data);
	if (data->effects & 2)
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	else if (~data->effects & 2)
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	set_effects(keydata, data);
}
