/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:10:41 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/16 05:14:32 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move(t_data *data)
{
    float       angle;

    if (mlx_is_key_down(data->mlx, MLX_KEY_W)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_S))
        check_collision(data, data->d_x, data->d_y);
    if (mlx_is_key_down(data->mlx, MLX_KEY_S)
		&& !mlx_is_key_down(data->mlx, MLX_KEY_W))
        check_collision(data, data->d_x * -1, data->d_y * -1);
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
	if (data->speed == DASH)
		data->speed = WALK;
	player_move(data);
}
