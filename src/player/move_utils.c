/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:29:32 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/15 05:50:01 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_dash(t_data *data)
{
	data->speed = DASH;
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
		data->speed = SPRINT;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_C)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
		data->speed = SNEAK;
	else
		data->speed = WALK;
}

/**
 * Returns input angle converted to 0 < angle < PI2.
 */
float	angle_fit(float angle)
{
	while (angle < 0)
		angle += PI2;
	while (angle > PI2)
		angle -= PI2;
	return (angle);
}
