/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 06:29:16 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/17 02:23:22 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rays.h"

t_ray	init_ray(t_data *data, float angle)
{
	t_ray	ray;

	ray.angle = angle_fit(angle);
	ray.s.x = 0;
	ray.s.y = 0;
	ray.r.x = 0;
	ray.r.y = 0;
	ray.d.x = (sin(angle));
	ray.d.y = (cos(angle));
	// printf("ray dx %f ray dy %f, angle %f\n", ray.d.x, ray.d.y, ray.angle);
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
	int	color = 15000000;

	i = 0;
	j = 0;
	// if (!((ray.p.x > 0 && ray.p.x < data->map_->width * data->ts)
	// 	&& (ray.p.y > 0 && ray.p.y < data->map_->height * data->ts)))
	// 	return ;
	// printf("ray: %f, full minus: %f\n", ray.angle, PI2 - ray.angle);
	// printf("TAN %f\n", atan(angle_fit(ray.angle)));
	if (ray.angle > M_PI)
	{
		ray.r.y = (((int)ray.p.y >> 6) << 6);
		ray.r.x = (ray.p.y - ray.r.y) * atan((PI2 - ray.angle)) + ray.p.x;
		ray.o.y = -64;
		ray.o.x = -ray.o.y * cos((PI2 - ray.angle - PI2));
	}
	if (ray.angle < M_PI)
	{
		ray.r.y = (((int)ray.p.y >> 6) << 6) + 64;
		ray.r.x = (ray.p.y - ray.r.y) * atan((PI2 - ray.angle)) + ray.p.x;
		ray.o.y = 64;
		ray.o.x = ray.o.y * cos((PI2 - ray.angle));
	}
	if (ray.angle == 0 || ray.angle == M_PI)
	{
		ray.r.x = ray.p.x;
		ray.r.y = ray.p.y;
		j = 30;
	}
	printf("rx %f, ry %f, py %f, ox %f, oy %f\n",ray.r.x, ray.r.y, ray.p.y, ray.o.x, ray.o.y);
	while (j < 4)
	{
		ray.m.x = (int)ray.r.x>>6;
		ray.m.y = (int)ray.r.y>>6;
		// printf("m.x %u, r.x %f,  m.y %u, width %u, height %u\n", ray.m.x, ray.r.x, ray.m.y, data->map_->width, data->map_->height);
		if (ray.r.x > (data->map_->width) * 64|| ray.r.y > (data->map_->height) * 64
			|| ray.r.x < 0 || ray.r.y < 0)
		{
			j = 4;
			// printf("breaking\n");
			break ;
		}
		// printf("m.x %u,  m.y %u, width %u, height %u\n", ray.m.x, ray.m.y, data->map_->width, data->map_->height);
		if (ray.m.x < (int)data->map_->width
			&& ray.m.y < (int)data->map_->height
			&& data->map[ray.m.y][ray.m.x] == '1')
		{
			j = 4;
			// printf("want to put x %f y %f\n", ray.r.x, ray.r.y);
			mlx_put_pixel(data->rays, ray.r.x, ray.r.y, color);
			// mlx_put_pixel(data->rays, ray.r.x, ray.r.y + 1, 255);
			// mlx_put_pixel(data->rays, ray.r.x, ray.r.y + 2, 255);
			// mlx_put_pixel(data->rays, ray.r.x, ray.r.y - 1, 255);
			// mlx_put_pixel(data->rays, ray.r.x, ray.r.y - 2, 255);
		}
		else
		{
			// printf("want to put x %f y %f\n", ray.r.x, ray.r.y);
			mlx_put_pixel(data->rays, ray.r.x, ray.r.y, color);
			mlx_put_pixel(data->rays, ray.r.x, ray.r.y + 1, color);
			mlx_put_pixel(data->rays, ray.r.x, ray.r.y + 2, color);
			mlx_put_pixel(data->rays, ray.r.x, ray.r.y - 1, color);
			mlx_put_pixel(data->rays, ray.r.x, ray.r.y - 2, color);
			ray.r.x += ray.o.x;
			ray.r.y += ray.o.y;
			j++;
		}
	}
	// mlx_put_pixel(data->rays, ray.p.x, ray.p.y, 0x00FF00FF);
	// ray.p.x = ray.p.x + ray.d.x;
	// ray.p.y = ray.p.y + ray.d.y;
	// i += 0.01;
}

void	do_rays(t_data *data)
{
	float	angle;

	ft_memset(data->rays->pixels, 0,
		data->map_->width * data->ts * data->map_->height * data->ts * sizeof(int));
	angle = angle_fit(data->angle - M_PI_4);//this is actually right one
	// angle = angle_fit(data->angle);//this for testing only
	// printf("%f angle\n", angle);
	while (angle < data->angle + M_PI_4)
	{
		one_ray(data, init_ray(data, angle));
		angle += 0.006544984694979;
	}
}
