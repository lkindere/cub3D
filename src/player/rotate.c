/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:10:41 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/14 22:37:15 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_strafe(t_data *data)
{
	t_player	*player;
	float		temp_x;
	float		temp_y;

	player = data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		temp_x = player->angle + M_PI_2;
		if (temp_x < 0)
			temp_x += PI2;
		if (temp_x > PI2)
			temp_x -= PI2;
		temp_y = sin(temp_x);
		temp_x = cos(temp_x);
		player->img->instances[0].x += temp_x * player->speed;
		player->img->instances[0].y += temp_y * player->speed;
		// player->img->instances[0].x -= cos(fmod(player->angle - M_PI_2, M_PI)) * player->speed;
		// player->img->instances[0].y -= sin(fmod(player->angle - M_PI_2, M_PI)) * player->speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		temp_x = player->angle - M_PI_2;
		if (temp_x < 0)
			temp_x += PI2;
		if (temp_x > PI2)
			temp_x -= PI2;
		temp_y = sin(temp_x);
		temp_x = cos(temp_x);
		player->img->instances[0].x += temp_x * player->speed;
		player->img->instances[0].y += temp_y * player->speed;
		// player->img->instances[0].x += cos(fmod(player->dx + M_PI_2, M_PI)) * player->speed;
		// player->img->instances[0].y += sin(fmod(player->dy + M_PI_2, M_PI)) * player->speed;
	}
}

void	player_rotate(t_data *data)
{
	t_player	*player;

	player = data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
			player->angle -= 0.1;
		if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
			player->angle += 0.1;
		if (player->angle < 0)
			player->angle += PI2;
		if (player->angle > PI2)
			player->angle -= PI2;
		player->dx = cos(player->angle);
		player->dy = sin(player->angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		player->img->instances[0].x += player->dx * player->speed;
		player->img->instances[0].y += player->dy * player->speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		player->img->instances[0].x -= player->dx * player->speed;
		player->img->instances[0].y -= player->dy * player->speed;
	}
	player_strafe(data);
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
