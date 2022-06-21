/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:39:57 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/21 22:47:21 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_raycast
{
	int		raycount;
	float	ray_step;
	float	pixel_step;
	float	pixel_offset;
	float	angle;
	float	angle_offset;
	t_vec	pixel;
	t_vec	dir;
	t_ray	ray;
}	t_raycast;

//Casts 2 rays in both directions
static void	cast_rays(t_data *data, t_raycast *rc)
{
	rc->dir.x = cos(rc->angle + rc->angle_offset);
	rc->dir.y = sin(rc->angle + rc->angle_offset);
	rc->ray = do_rays(data, data->player, rc->dir, -1);
	if (rc->ray.hit_pos != NO_POS)
	{
		rc->ray.distance *= cos(rc->angle + rc->angle_offset - data->angle);
		draw_rays(data, &rc->ray,
			vector(rc->pixel.x + rc->pixel_offset, rc->pixel.y));
	}
	rc->dir.x = cos(rc->angle - rc->angle_offset);
	rc->dir.y = sin(rc->angle - rc->angle_offset);
	rc->ray = do_rays(data, data->player, rc->dir, -1);
	if (rc->ray.hit_pos == NO_POS)
		return ;
	rc->ray.distance *= cos(rc->angle - rc->angle_offset - data->angle);
	draw_rays(data, &rc->ray,
		vector(rc->pixel.x - rc->pixel_offset, rc->pixel.y));
}

void	raycaster(t_data *data)
{
	t_raycast	rc;
	int			i;

	i = -1;
	rc.angle_offset = 0;
	rc.pixel_offset = 0;
	rc.ray_step = 1.0 / data->width;
	rc.raycount = data->width;
	rc.pixel = vector(data->width / 2, data->height / 2);
	rc.angle = data->angle;
	rc.pixel_step = (float)data->width / rc.raycount;
	while (++i < rc.raycount / 2)
	{
		cast_rays(data, &rc);
		rc.angle_offset += rc.ray_step;
		rc.pixel_offset += rc.pixel_step;
		rc.ray_step -= rc.ray_step / 2000;
	}
}
