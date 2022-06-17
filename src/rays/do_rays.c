/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 06:29:16 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/17 06:15:53 by lkindere         ###   ########.fr       */
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


void safe_pixel(mlx_image_t* image, t_data *data, t_vec vec, uint32_t color)
{
	if (vec.x < 1 || vec.x > data->mlx->width - 1)
		return ;
	if (vec.y < 1 || vec.y > data->mlx->height - 1)
		return ;
	mlx_put_pixel(image, vec.x, vec.y, color);
}

void	do_rays(t_data *data)
{
	t_vec_int	map;
	t_vec		step;
	t_vec		start;
	t_vec		dir;
	t_vec		len;

	map.x = data->p_x;
	map.y = data->p_y;
	start.x = data->p_x;
	start.y = data->p_y;
	dir.x = data->d_x;
	dir.y = data->d_y;

	printf("Angle: %f, d_x: %f, d_y: %f, p_x: %f, p_y: %f\n", 
		data->angle, data->d_x, data->d_y, data->p_x, data->p_y);
		
	step.x = sqrt(1 + (dir.y / dir.x) * (dir.y / dir.x));
	step.y = sqrt(1 + (dir.x / dir.y) * (dir.x / dir.y));
	// printf("Start x: %f, start xint: %d\n", start.x, (int)start.x);


	if (dir.x < 0)
		len.x = (start.x - map.x) * step.x;
	if (dir.x > 0)
		len.x = ((float)(map.x + 1) - start.x) * step.x;
	if (dir.y < 0)
		len.y = (start.y - map.y) * step.y;
	if (dir.y > 0)
		len.y = ((float)start.y + 1 - start.y) * step.y;
	
	if (len.x < len.y)
	{
		t_vec	draw;

		for (float i = 0; i < len.x; i += 0.01)
		{
			draw.x = ((start.x) * data->ts);
			draw.y = (start.y + i) * data->ts;

			safe_pixel(data->rays, data, draw, 0x00FF00FF);
		}
		printf("X axis is shorter\n");
	}
	else
	{
		t_vec	draw;

		for (float i = 0; i < len.y; i += 0.01)
		{
			draw.x = ((start.x + i) * data->ts);
			draw.y = (start.y) * data->ts;

			safe_pixel(data->rays, data, draw, 0x00FFF0FF);
		}
		printf("Y axis is shorter\n");
	}
	printf("Step x: %f\n", step.x);
	printf("X len: %f\n", len.x);
	// printf("Step y: %f\n", step.y);
	// printf("Y len: %f\n", len.y);
}
