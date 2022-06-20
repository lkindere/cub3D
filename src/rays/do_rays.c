/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 06:29:16 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/20 10:21:28 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ray	ray_init(t_data *data, t_ray *r)
{
	r->map = set_vector_int(r->start.x, r->start.y);
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

static void	ray_step(t_ray *r)
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

t_ray	do_rays(t_data *data, t_vec start, t_vec dir, float range)
{
	t_ray	r;

	r.dir = dir;
	r.start = start;
	ray_init(data, &r);
	while (1)
	{
		ray_step(&r);
		if (range != -1 && r.distance > range)
			break ;
		if (r.map.x >= data->map_->width || r.map.y >= data->map_->height
			|| r.map.x < 0 || r.map.y < 0)
			break ;
		if (data->map[r.map.y][r.map.x] == '1')
		{
			r.hit.x = r.start.x + dir.x * r.distance;
			r.hit.y = r.start.y + dir.y * r.distance;

			t_vec	hit64;
			hit64.x = (r.start.x) * 64 + dir.x * (r.distance * 64);
			hit64.y = (r.start.y) * 64 + dir.y * (r.distance * 64);
			draw_line(data->rays, set_vector(data->p_x * 64, data->p_y * 64),
				hit64, 0xFF0000FF);
			return (r);
		}
	}
	r.hit = set_vector(-1, -1);
	return (r);
}
