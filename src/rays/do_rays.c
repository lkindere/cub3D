/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 06:29:16 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/18 13:59:08 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Map: 		int representation of starting tile
//Start: 	Starting x and y
//Dir:		Starting direction
//Len:		Length in x or y
//Step:		Unit step size in x or y
//Hit:		Wall hit x and y
//Distance:	Distance to wall hit
typedef struct s_ray
{
	t_vec_int	map;
	t_vec		start;
	t_vec		dir;
	t_vec		len;
	t_vec		step;
	t_vec		hit;
	float		distance;
}	t_ray;

t_ray	ray_init(t_data *data, t_ray *r)
{
	r->map = set_vector_int(data->p_x, data->p_y);
	r->start = set_vector(data->p_x, data->p_y);
	r->dir = set_vector(data->d_x, data->d_y);
	r->step.x = sqrt(1 + (r->dir.y / r->dir.x) * (r->dir.y / r->dir.x));
	r->step.y = sqrt(1 + (r->dir.x / r->dir.y) * (r->dir.x / r->dir.y));
	if (r->dir.x < 0)
	{
		r->dir.x = -1;
		r->len.x = (r->start.x - r->map.x) * r->step.x;
	}
	if (r->dir.x > 0)
	{
		r->dir.x = 1;
		r->len.x = ((float)r->map.x + 1 - r->start.x) * r->step.x;
	}
	if (r->dir.y < 0)
	{
		r->dir.y = -1;
		r->len.y = (r->start.y - r->map.y) * r->step.y;
	}
	if (r->dir.y > 0)
	{
		r->dir.y = 1;
		r->len.y = ((float)r->map.y + 1 - r->start.y) * r->step.y;
	}
}

void	ray_step(t_ray *r)
{
	if (r->len.x < r->len.y)
	{
		r->map.x += r->dir.x;
		r->distance = r->len.x;
		r->len.x += r->step.x;
	}
	else if (r->len.y < r->len.x)
	{
		r->map.y += r->dir.y;
		r->distance = r->len.y;
		r->len.y += r->step.y;
	}
}

void	do_rays(t_data *data)
{
	t_ray	r;

	ray_init(data, &r);
	while (1)
	{
		ray_step(&r);
		if (r.map.x >= data->map_->width || r.map.y >= data->map_->height
			|| r.map.x < 0 || r.map.y < 0)
			break ;
		if (data->map[r.map.y][r.map.x] == '1')
		{
			r.hit.x = (r.start.x) * 64 + data->d_x * (r.distance * 64);
			r.hit.y = (r.start.y) * 64 + data->d_y * (r.distance * 64);
			draw_line(data->rays, set_vector(data->p_x * 64, data->p_y * 64),
				r.hit, 0xFF0000FF);
			printf("Distance to wall: %f\n", r.distance);
			break ;
		}
	}
}
