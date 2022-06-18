/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 06:29:16 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/18 13:19:33 by lkindere         ###   ########.fr       */
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
	t_vec_int	map;
	t_vec		step;
	t_vec		start;
	t_vec		dir;
	t_vec		len;
	t_vec		hit;
	float		distance;

	map = set_vector_int(data->p_x, data->p_y);
	start = set_vector(data->p_x, data->p_y);
	dir = set_vector(data->d_x, data->d_y);

	// printf("Angle: %f, d_x: %f, d_y: %f, p_x: %f, p_y: %f\n\n", 
	// 	data->angle, data->d_x, data->d_y, data->p_x, data->p_y);
		
	step.x = sqrt(1 + (dir.y / dir.x) * (dir.y / dir.x));	//Unit step in x direction
	step.y = sqrt(1 + (dir.x / dir.y) * (dir.x / dir.y));	//Unit step in y direction

	printf("Unit step X: %f, Y: %f\n\n", step.x, step.y);
	if (dir.x < 0)
	{
		dir.x = -1;
		len.x = (start.x - (map.x)) * step.x;
	}
	if (dir.x > 0)
	{
		dir.x = 1;
		len.x = ((float)map.x + 1 - start.x) * step.x;
	}
	if (dir.y < 0)
	{
		dir.y = -1;
		len.y = (start.y - (map.y)) * step.y;
	}
	if (dir.y > 0)
	{
		dir.y = 1;
		len.y = ((float)map.y + 1 - start.y) * step.y;
	}
	t_vec	player;

	player = set_vector(data->p_x * 64, data->p_y * 64);
	while (1)
	{
		if (len.x < len.y)
		{
			map.x += dir.x;
			distance = len.x;
			len.x += step.x;
		}
		else if (len.y < len.x)
		{
			map.y += dir.y;
			distance = len.y;
			len.y += step.y;
		}
		if (map.x >= data->map_->width || map.y >= data->map_->height
			|| map.x < 0 || map.y < 0)
			break ;
		if (data->map[map.y][map.x] == '1')
		{
			hit.x = (start.x) * 64 + data->d_x * (distance * 64); 
			hit.y = (start.y) * 64 + data->d_y * (distance * 64);
			draw_line(data->rays, player, hit, 0xFF0000FF);
			break ;
		}
	}

	// wall.x = player.x + (sin(data->angle * -1 + M_PI_2) * (len.y * 64));
	// wall.y = player.y + (cos(data->angle * -1 + M_PI_2) * (len.y * 64));
	// draw_line(data->rays, player, wall, 0xFF0000FF);
	// printf("Player x: %f, player y: %f\n", player.x, player.y);
	// printf("Wall x: %f, wall y: %f\n", wall.x, wall.y);
}
