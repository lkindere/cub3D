/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 06:29:16 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/18 07:43:07 by lkindere         ###   ########.fr       */
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

	if (dir.x < 0)
		len.x = (start.x - map.x) * step.x;
	if (dir.x > 0)
		len.x = ((float)(map.x + 1) - start.x) * step.x;
	if (dir.y < 0)
		len.y = (start.y - map.y) * step.y;
	if (dir.y > 0)
		len.y = ((float)start.y + 1 - start.y) * step.y;

	printf("\nDist X: %f, dist Y: %f\n", len.x, len.y);
	printf("Step X: %f, step Y: %f\n\n", step.x, step.y);


	t_vec	player;
	t_vec	wall;

	player.x = (data->p_x) * 64;
	player.y = (data->p_y) * 64;
	if (len.x < len.y)
	{
		wall.x = player.x + (sin(data->angle * -1 + M_PI_2) * (len.x * 64));
		wall.y = player.y + (cos(data->angle * -1 + M_PI_2) * (len.x * 64));
		draw_line(data->rays, player, wall, 0x0000FFFF);
	}
	if (len.y < len.x)
	{
		wall.x = player.x + (sin(data->angle * -1 + M_PI_2) * (len.y * 64));
		wall.y = player.y + (cos(data->angle * -1 + M_PI_2) * (len.y * 64));
		draw_line(data->rays, player, wall, 0xFF0000FF);
	}
	// printf("Sin of data angle: %f\n", sin(data->angle));
	// printf("Cos of data angle: %f\n", cos(data->angle));
	// printf("Player x: %f, player y: %f\n", player.x, player.y);
	// printf("Wall x: %f, wall y: %f\n", wall.x, wall.y);
}
