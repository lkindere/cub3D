/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 06:29:16 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/17 22:44:51 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	width;
int	height;

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

void	do_rays(t_data *data)
{
	width = data->mlx->width - 1;
	height = data->mlx->height -1;
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

	// printf("Angle: %f, d_x: %f, d_y: %f, p_x: %f, p_y: %f\n", 
		// data->angle, data->d_x, data->d_y, data->p_x, data->p_y);
		
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

			safe_pixel(data->rays, draw, 0x00FF00FF);
		}
		// printf("X axis is shorter\n");
	}
	else
	{
		t_vec	draw;

		for (float i = 0; i < len.y; i += 0.01)
		{
			draw.x = ((start.x + i) * data->ts);
			draw.y = (start.y) * data->ts;

			safe_pixel(data->rays, draw, 0x00FFF0FF);
		}
		// printf("Y axis is shorter\n");
	}
	// printf("Step x: %f\n", step.x);
	// printf("X len: %f\n", len.x);
	t_vec p1;
	t_vec p2;

	p1.x = 0;
	p1.y = 0;
	p2.x = 200;
	p2.y = 500;
	draw_line(data->rays, p1, p2, 0x00FFF0FF);
	p1.x = 200;
	p2.y = 0;
	p2.x = 200;
	p2.y = 500;
		draw_line(data->rays, p1, p2, 0x00FFF0FF);
	p1.x = 400;
	p2.y = 0;
	p2.x = 200;
	p2.y = 200;
			draw_line(data->rays, p1, p2, 0x00FFF0FF);
		p1.x = 400;
	p2.y = 0;
	p2.x = 700;
	p2.y = 600;
			draw_line(data->rays, p1, p2, 0x00FFF0FF);
				p1.x = 1000;
	p2.y = 500;
	p2.x = 200;
	p2.y = 200;
			draw_line(data->rays, p1, p2, 0x00FFF0FF);
	// printf("Step y: %f\n", step.y);
	// printf("Y len: %f\n", len.y);
}
