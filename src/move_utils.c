/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_modifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:29:32 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/14 13:40:24 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * If either left shift or C is pressed, modifies the movement speed.
 * If both or none are pressed, keeps speed at normal walking speed.
 */
void	player_speed(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_C))
		data->player->speed = SPRINT;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_C)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
		data->player->speed = SNEAK;
	else
		data->player->speed = WALK;
}
