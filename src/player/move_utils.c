/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:29:32 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/15 00:48:39 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_dash(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_up(data, DASH);
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_down(data, DASH);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left(data, DASH);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right(data, DASH);
}

/**
 * If either left shift or C is pressed, modifies the movement speed.
 * If both or none are pressed, keeps speed at normal walking speed.
 */
void	player_speed(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_C))
		data->speed = SPRINT;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_C)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
		data->speed = SNEAK;
	else
		data->speed = WALK;
}
