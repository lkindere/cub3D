/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 06:29:16 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/15 07:29:07 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//add a struct for this stuff here. this file only
void	one_ray(t_data *data, float x, float y, float angle, float d_y)
{
	float	i;
	float	d_x;
	float	r_x;
	float	r_y;

	i = 0;
	d_x = cos(angle);
	while (i < 100)
	{
		if (!((x > 0 && x < data->map_->width * data->ts)
			&& (y > 0 && y < data->map_->height * data->ts)))
			break ;
		if (angle > M_PI)
		{
			r_y = (((int)y >> 6) << 6) - 0.0001;
			r_x = (y - r_y) * atan(angle) + x;
		}
		mlx_put_pixel(data->rays, x, y, 0x00FF00FF);
		x = x + d_x;
		y = y + d_y;
		i += 0.01;
	}
}

void	do_rays(t_data *data)
{
	float	angle;

	ft_memset(data->rays->pixels, 0,
		data->map_->width * data->ts * data->map_->height * data->ts * sizeof(int));
	angle = data->angle - M_PI_4;
	while (angle < data->angle + M_PI_4)
	{
		one_ray(data, data->p_x, data->p_y, angle, sin(angle));
		angle += 0.006544984694979;
	}
}