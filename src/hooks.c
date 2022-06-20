/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:18:21 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/20 10:26:20 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	play_dir_line(t_data *data)
{
	t_vec	p1;
	t_vec	p2;

	p1 = set_vector(data->p_x * data->ts, data->p_y * data->ts);
	p2 = set_vector(p1.x + data->d_x * 32, p1.y + data->d_y * 32);
	draw_line(data->rays, p1, p2, 0x00FF00FF);
}

void	reset_images(t_data *data)
{
	ft_memset(data->rays->pixels, 0,
		data->map_->width * data->ts * data->map_->height * data->ts * sizeof(int));
	ft_memset(data->draw->pixels, 0,
		data->map_->width * data->ts * data->map_->height * data->ts * sizeof(int));
	data->p_img->instances[0].x = (data->p_x - data->ps / 2) * data->ts;
	data->p_img->instances[0].y = (data->p_y - data->ps / 2) * data->ts;
	play_dir_line(data);
}

typedef struct s_raycast
{
	int		raycount;
	float	ray_step;
	float	pixel_step;
	float	angle;
	t_vec	pixel;
	t_vec	dir;
	t_ray	ray;
} t_raycast;


void	cast_rays(t_data *data)
{
	t_raycast	rc;
	float		angle_offset;
	float		pixel_offset;
	int			i;

	i = -1;
	angle_offset = 0;
	pixel_offset = 0;
	rc.ray_step = 1.0 / data->draw->width;
	rc.raycount = data->draw->width;
	rc.pixel = set_vector(data->draw->width / 2, data->draw->height / 2);
	rc.angle = data->angle;
	rc.pixel_step = (float)data->draw->width / rc.raycount;
	while (++i < rc.raycount / 2)
	{
		rc.dir = set_vector(cos(rc.angle + angle_offset), sin(rc.angle + angle_offset));
		rc.ray = do_rays(data, set_vector(data->p_x, data->p_y), rc.dir, -1);
		rc.ray.distance *= cos(rc.angle + angle_offset - data->angle);
		draw_rays(data, rc.ray, set_vector(rc.pixel.x + pixel_offset, rc.pixel.y));
		rc.dir = set_vector(cos(rc.angle - angle_offset), sin(rc.angle - angle_offset));
		rc.ray = do_rays(data, set_vector(data->p_x, data->p_y), rc.dir, -1);
		rc.ray.distance *= cos(rc.angle - angle_offset - data->angle);
		draw_rays(data, rc.ray, set_vector(rc.pixel.x - pixel_offset, rc.pixel.y));
		
		angle_offset += rc.ray_step;
		pixel_offset += rc.pixel_step;
		rc.ray_step -= rc.ray_step / 1000;
	}
}

void	hook(void* param)
{
	t_data	*data;

	data = param;
	player_speed(data);
	player_rotate(data);
	data->angle = angle_fit(data->angle);
	reset_images(data);
	cast_rays(data);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_R)
	{
		data->p_x = 2.5;
		data->p_y = 2.5;
	}
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		player_dash(data);
}
