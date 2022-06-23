/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:10:41 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/23 16:19:52 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	reset_mouse(t_data *data, int mouse[2])
{
	if (data->mouse.x < 0 || data->mouse.x > data->width)
		mlx_set_mouse_pos(data->mlx, data->width / 2, mouse[1]);
	if (data->mouse.y < 0 || data->mouse.y > data->height)
		mlx_set_mouse_pos(data->mlx, mouse[0], data->height / 2);
}

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
	if (~data->effects & 2
		&& data->mouse.x >= 0 && data->mouse.x <= data->width)
		data->angle -= (data->mouse.x - mouse[0]) / 500;
	data->dir = vector(cos(data->angle), sin(data->angle));
	data->mouse.x = mouse[0];
	data->mouse.y = mouse[1];
	if (~data->effects & 2)
		reset_mouse(data, mouse);
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
