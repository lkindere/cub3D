/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:18:21 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/20 08:06:31 by lkindere         ###   ########.fr       */
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

void	cast_rays(t_data *data)
{
	float	ray_step;
	float	pixel_step;
	float	temp_angle;
	int		raycount;
	t_vec	start;
	t_vec	dir;
	t_ray	r;

	ray_step = 0.0025;
	raycount = 300;
	start = set_vector(data->map_->width * data->ts / 2, data->map_->height * data->ts / 2);
	temp_angle = angle_fit(data->angle - (ray_step * raycount / 2));
	pixel_step = (float)data->rays->width / raycount;
	start.x -= pixel_step * raycount / 2;
	while (raycount)
	{
		dir = set_vector(cos(temp_angle), sin(temp_angle));
		r = do_rays(data, set_vector(data->p_x, data->p_y), dir, -1);
		r.distance *= cos(temp_angle - data->angle);
		draw_rays(data, r, start);
		temp_angle = angle_fit(temp_angle += ray_step);
		
		start.x += pixel_step;
		raycount--;
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
