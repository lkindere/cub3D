/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:18:21 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/20 11:22:44 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	play_dir_line(t_data *data)
{
	t_vec	p1;
	t_vec	p2;

	p1 = mult_vector(data->player, TS);
	p2 = add_vector(p1, vector(data->dir.x * TS, data->dir.y * TS));
	draw_line(data->rays, p1, p2, 0x00FF00FF);
}

void	reset_images(t_data *data)
{
	ft_memset(data->rays->pixels, 0,
		data->map_->width * TS * data->map_->height * TS * sizeof(int));
	ft_memset(data->draw->pixels, 0,
		data->map_->width * TS * data->map_->height * TS * sizeof(int));
	data->p_img->instances[0].x = (data->player.x - PS / 2) * TS;
	data->p_img->instances[0].y = (data->player.y - PS / 2) * TS;
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
	rc.pixel = vector(data->draw->width / 2, data->draw->height / 2);
	rc.angle = data->angle;
	rc.pixel_step = (float)data->draw->width / rc.raycount;
	while (++i < rc.raycount / 2)
	{
		rc.dir = vector(cos(rc.angle + angle_offset), sin(rc.angle + angle_offset));
		rc.ray = do_rays(data, data->player, rc.dir, -1);
		rc.ray.distance *= cos(rc.angle + angle_offset - data->angle);
		draw_rays(data, rc.ray, vector(rc.pixel.x + pixel_offset, rc.pixel.y));
		rc.dir = vector(cos(rc.angle - angle_offset), sin(rc.angle - angle_offset));
		rc.ray = do_rays(data, data->player, rc.dir, -1);
		rc.ray.distance *= cos(rc.angle - angle_offset - data->angle);
		draw_rays(data, rc.ray, vector(rc.pixel.x - pixel_offset, rc.pixel.y));
		
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
		data->player = vector(2.5, 2.5);
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		player_dash(data);
}
