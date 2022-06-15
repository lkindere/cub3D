/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:10:41 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/15 02:45:40 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move(t_data *data)
{
	float		temp_x;
	float		temp_y;

	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		temp_x = data->angle - M_PI_2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		temp_x = data->angle + M_PI_2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A)
		|| mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		temp_x = angle_fit(temp_x);
		temp_y = sin(temp_x);
		temp_x = cos(temp_x);
		data->p_x += temp_x * data->speed;
		data->p_y += temp_y * data->speed;
	}
}

void	player_rotate(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
			data->angle -= 0.1  * data->mlx->delta_time * 60;
		if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
			data->angle += 0.1  * data->mlx->delta_time * 60;
		if (data->angle < 0)
			data->angle += PI2;
		if (data->angle > PI2)
			data->angle -= PI2;
		data->d_x = cos(data->angle);
		data->d_y = sin(data->angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->p_x += data->d_x * data->speed * data->mlx->delta_time * 60;
		data->p_y += data->d_y * data->speed * data->mlx->delta_time * 60;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->p_x -= data->d_x * data->speed;
		data->p_y -= data->d_y * data->speed;
	}
	player_move(data);
	// if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	// {
	// 	player->img->instances[0].x -= cos(fmod(player->angle - M_PI_2, M_PI)) * player->speed;
	// 	player->img->instances[0].y -= sin(fmod(player->angle - M_PI_2, M_PI)) * player->speed;
	// }
	// if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	// {
	// 	player->img->instances[0].x += cos(fmod(player->dx + M_PI_2, M_PI)) * player->speed;
	// 	player->img->instances[0].y += sin(fmod(player->dy + M_PI_2, M_PI)) * player->speed;
	// }
}
