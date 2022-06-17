/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:10:41 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/16 22:15:17 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_rotate(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
			data->angle -= 0.1  * data->mlx->delta_time * 60;
		if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
			data->angle += 0.1  * data->mlx->delta_time * 60;
		// if (data->angle < 0)
		// 	data->angle += PI2;
		// if (data->angle > PI2)
		// 	data->angle -= PI2;
		data->d_x = cos(data->angle);
		data->d_y = sin(data->angle);
	}
	player_move(data);
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
