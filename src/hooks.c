/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:18:21 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/19 01:48:11 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	play_dir_line(t_data *data)
{
	t_vec	p1;
	t_vec	p2;

	p1 = set_vector(data->p_x * data->ts, data->p_y * data->ts);
	p2 = set_vector(p1.x + data->d_x * 32, p1.y + data->d_y * 32);
	draw_line(data->rays, p1, p2, 0x00FF00FF);
}

void	hook(void* param)
{
	t_data	*data;

	data = param;
	player_speed(data);
	player_rotate(data);
	data->angle = angle_fit(data->angle);
	ft_memset(data->rays->pixels, 0,
		data->map_->width * data->ts * data->map_->height * data->ts * sizeof(int));
	do_rays(data, set_vector(data->p_x, data->p_y), set_vector(data->d_x, data->d_y), -1);
	data->p_img->instances[0].x = (data->p_x - data->ps / 2 )* data->ts;
	data->p_img->instances[0].y = (data->p_y - data->ps / 2) * data->ts;
	play_dir_line(data);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_R)
	{
		data->p_x = 2.5;
		data->p_y = 2.5;
	}
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		player_dash(data);
}
