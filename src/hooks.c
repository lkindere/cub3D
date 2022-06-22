/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:18:21 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/21 23:50:07 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int funky_stuff(unsigned int color)
{
	return (color + (rand() % 255));
}

void	reset_background(t_data *data, uint32_t ceiling, uint32_t floor)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < data->draw->height / 2)
	{
		while (data->effects & 4 && ++j < data->draw->width)
			mlx_put_pixel(data->draw, j, i, funky_stuff(ceiling));
		while (++j < data->draw->width)
			mlx_put_pixel(data->draw, j, i, ceiling);
		j = -1;
	}
	while (i < data->draw->height)
	{
		while (data->effects & 8 && ++j < data->draw->width)
			mlx_put_pixel(data->draw, j, i, funky_stuff(floor));
		while (++j < data->draw->width)
			mlx_put_pixel(data->draw, j, i, floor);
		j = -1;
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
	printf("Fps: %f\n", 1 / data->mlx->delta_time);
	player_speed(data);
	player_rotate(data);
	data->angle = angle_fit(data->angle);
	reset_images(data);
	raycaster(data);
}

//1	Toggles mouse on/off 	[1]
//2 Toggles minimap rays 	[2]
//3 Toggles funky ceilings	[4]
//4 Toggles funky floors	[8]
void	set_effects(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		data->effects ^= 1;
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
		data->effects ^= 2;
	if (keydata.key == MLX_KEY_3 && keydata.action == MLX_PRESS)
		data->effects ^= 4;
	if (keydata.key == MLX_KEY_4 && keydata.action == MLX_PRESS)
		data->effects ^= 8;
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
	set_effects(keydata, data);
}
