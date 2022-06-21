/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:10:41 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/21 17:44:41 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_rotate(t_data *data)
{
	int	mouse[2];

	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
			data->angle -= (1 * SPEED_MULTIPLIER) * data->mlx->delta_time * 60;
		if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
			data->angle += (1 * SPEED_MULTIPLIER) * data->mlx->delta_time * 60;
		data->angle = angle_fit(data->angle);
	}
	mlx_get_mouse_pos(data->mlx, &mouse[0], &mouse[1]);
	if (data->mouse.x >= 0 && data->mouse.x <= WIDTH)
		data->angle -= (data->mouse.x - mouse[0]) / 100;
	data->dir = vector(cos(data->angle), sin(data->angle));
	data->mouse.x = mouse[0];
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
