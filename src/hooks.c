/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:18:21 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/17 05:04:56 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	play_dir_line(t_data *data)
{
	for (float i = 0; i < 30; i += 1)
	{
		mlx_put_pixel(data->rays, data->p_x * data->ts + data->d_x * i,
			data->p_y * data->ts + data->d_y * i, 0x00FF00FF);
	}
}

int i = 0;

void	hook(void* param)
{
	t_data	*data;

	data = param;
	player_speed(data);
	player_rotate(data);
	data->angle = angle_fit(data->angle);
	ft_memset(data->rays->pixels, 0,
		data->map_->width * data->ts * data->map_->height * data->ts * sizeof(int));
	// if (i == 50)
	// {
		do_rays(data);
		// i = 0;
		// printf("Px py %f %f\n", data->p_x, data->p_y);
	// }
	i++;
	play_dir_line(data);
	data->p_img->instances[0].x = (data->p_x - data->ps / 2 )* data->ts;
	data->p_img->instances[0].y = (data->p_y - data->ps / 2) * data->ts;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_R)
	{
		data->p_x = 2 * data->ts;
		data->p_y = 2 * data->ts;
	}
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		player_dash(data);
	// printf("Angle: %f, d_x: %f, d_y: %f, p_x: %f, p_y: %f\n", 
	// 	data->angle, data->d_x, data->d_y, data->p_x, data->p_y);
	// printf("X: %f\tY: %f\tangle: %f\tdx: %f\tdy: %f\tfps: %f\n", data->p_x, data->p_y, data->angle, data->d_x, data->d_y, 1 / data->mlx->delta_time);
}
