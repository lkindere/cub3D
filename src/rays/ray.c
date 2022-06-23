/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 06:29:16 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/23 15:46:44 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ray_init(t_ray *r)
{
	r->is_door = 0;
	r->map = vector_int(r->start.x, r->start.y);
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

static int	ray_step(t_ray *r)
{
	if (r->len.x <= r->len.y)
	{
		r->map.x += r->dir.x;
		r->distance = r->len.x;
		r->len.x += r->step.x;
		if (r->dir.x < 0)
			r->hit_pos = W;
		if (r->dir.x > 0)
			r->hit_pos = E;
	}
	else if (r->len.y < r->len.x)
	{
		r->map.y += r->dir.y;
		r->distance = r->len.y;
		r->len.y += r->step.y;
		if (r->dir.y < 0)
			r->hit_pos = N;
		if (r->dir.y > 0)
			r->hit_pos = S;
	}
	return (1);
}

void	hit_object(t_data *data, t_ray *r)
{
	t_door	*door;
	int		i;

	i = -1;
	door = data->map_->doors;
	while (door && door[++i].x != -1)
	{
		if (r->map.x == door[i].x && r->map.y == door[i].y && door[i].open == 0)
			r->is_door = 1;
		if (r->hit_pos == N && door[i].open == 1 && door[i].direction == 'Y'
			&& r->map.x == door[i].x && r->map.y + 1 == door[i].y)
			r->is_door = 1;
		if (r->hit_pos == S && door[i].open == 1 && door[i].direction == 'Y'
			&& r->map.x == door[i].x && r->map.y - 1 == door[i].y)
			r->is_door = 1;
		if (r->hit_pos == E && door[i].open == 1 && door[i].direction == 'X'
			&& r->map.x - 1 == door[i].x && r->map.y == door[i].y)
			r->is_door = 1;
		if (r->hit_pos == W && door[i].open == 1 && door[i].direction == 'X'
			&& r->map.x + 1 == door[i].x && r->map.y == door[i].y)
			r->is_door = 1;
	}
}

t_ray	do_rays(t_data *data, t_vec start, t_vec dir, float range)
{
	t_ray	r;

	r.dir = dir;
	r.start = start;
	ray_init(&r);
	while (ray_step(&r))
	{
		if (r.map.x >= data->map_->width || (range != -1 && r.distance > range)
			|| r.map.y >= data->map_->height || r.map.x < 0 || r.map.y < 0)
			break ;
		if (data->map[r.map.y][r.map.x] == '1')
		{
			hit_object(data, &r);
			r.hit.x = r.start.x + dir.x * r.distance;
			r.hit.y = r.start.y + dir.y * r.distance;
			if (data->effects & 1)
				draw_line(data->rays, mult_vector(data->player, data->tsm),
					mult_vector(r.hit, data->tsm), RAY_COLOR);
			return (r);
		}
	}
	r.hit_pos = NO_POS;
	return (r);
}
