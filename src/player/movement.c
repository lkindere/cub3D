/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 05:47:59 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/23 07:15:41 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move(t_data *data)
{
	float	angle;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_S))
		check_collision(data, data->dir.x, data->dir.y);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_W))
		check_collision(data, -data->dir.x, -data->dir.y);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_D))
		angle = data->angle - M_PI_2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_A))
		angle = data->angle + M_PI_2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A)
		!= mlx_is_key_down(data->mlx, MLX_KEY_D))
		check_collision(data, (cos(angle_fit(angle))), (sin(angle_fit(angle))));
}

void	player_dash(t_data *data)
{
	data->speed = SPEED_MULTIPLIER * DASH;
	player_move(data);
}

/**
 * If either left shift or C is pressed, modifies the movement speed.
 * If both or none are pressed, keeps speed at normal walking speed.
 */
void	player_speed(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_C))
		data->speed = SPEED_MULTIPLIER * SPRINT;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_C)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
		data->speed = SPEED_MULTIPLIER * SNEAK;
	else
		data->speed = SPEED_MULTIPLIER * WALK;
}
