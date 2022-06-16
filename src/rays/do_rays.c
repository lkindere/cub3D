/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 06:29:16 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/16 09:07:44 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rays.h"

t_ray	init_ray(t_data *data, float angle)
{
	t_ray	ray;

	ray.angle = angle;
	ray.r.x = 0;
	ray.r.y = 0;
	ray.d.x = cos(angle);
	ray.d.y = sin(angle);
	ray.p.x = data->p_x;
	ray.p.y = data->p_y;
	ray.o.x = 0;
	ray.o.y = 0;
	ray.m.x = 0;
	ray.m.y = 0;
	return (ray);
}

//add a struct for this stuff here. this file only
// void	one_ray(t_data *data, t_ray ray);
void	one_ray(t_data *data, t_ray ray)
{
	float	i;
	int		j;

	i = 0;
	j = 0;
	while (i < 100)
	{
		if (!((ray.p.x > 0 && ray.p.x < data->map_->width * data->ts)
			&& (ray.p.y > 0 && ray.p.y < data->map_->height * data->ts)))
			break ;
		if (ray.angle > M_PI)
		{
			ray.r.y = (((int)ray.p.y >> 6) << 6) - 0.0001;
			ray.r.x = (ray.p.y - ray.r.y) * angle_fit(atan(ray.angle)) + ray.p.x;
			ray.o.y = -64;
			ray.o.x = -ray.o.y * angle_fit(atan(ray.angle));
		}
		while (j < 30)
		{
			ray.m.x = (int)ray.r.x>>6;
			ray.m.y = (int)ray.r.y>>6;
			
			if (ray.m.x < data->map_->width
				// && ray.m.x > 0
				&& ray.m.y < data->map_->height
				// && ray.m.y > 0
				&& data->map[ray.m.y][ray.m.x] == '1')
			{
				j = 30;
				mlx_put_pixel(data->rays, ray.r.x, ray.r.y, 0x0000FFFF);
			}
			else
			{
				mlx_put_pixel(data->rays, ray.r.x, ray.r.y, 0x0000FFFF);
				ray.r.x += ray.o.x;
				ray.r.y += ray.o.y;
				j++;
			}
		}
		mlx_put_pixel(data->rays, ray.p.x, ray.p.y, 0x00FF00FF);
		ray.p.x = ray.p.x + ray.d.x;
		ray.p.y = ray.p.y + ray.d.y;
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
		one_ray(data, init_ray(data, angle));
		angle += 0.006544984694979;
	}
}