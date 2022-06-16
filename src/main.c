/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:15:33 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/16 05:14:49 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

int	is_wall(t_data *data, int x, int y, char **map)
{
	if (map[((int)data->p_y - data->ps / 2 + y) / data->ts]
		[((int)data->p_x - data->ps / 2 + x)  / data->ts] == '1')
		return (1);
	if (map[((int)data->p_y + data->ps / 2 + y) / data->ts]
		[((int)data->p_x + data->ps / 2 + x)  / data->ts] == '1')
		return (1);
	if (map[((int)data->p_y + data->ps / 2 + y) / data->ts]
		[((int)data->p_x - data->ps / 2 + x)  / data->ts] == '1')
		return (1);
	if (map[((int)data->p_y - data->ps / 2 + y) / data->ts]
		[((int)data->p_x + data->ps / 2 + x)  / data->ts] == '1')
		return (1);
	return (0);
}

int check_collision(t_data *data, float x, float y)
{
	x = x * data->speed * (data->mlx->delta_time * 60);
	y = y * data->speed * (data->mlx->delta_time * 60);
	while (is_wall(data, 0, y, data->map) && (int)y != 0)
	{
		if ((int)y < 0)
			y++;
		if ((int)y > 0)
			y--;
	}
	while (is_wall(data, x, 0, data->map) && (int)x != 0)
	{
		if ((int)x < 0)
			x++;
		if ((int)x > 0)
			x--;
	}
	data->p_x += (int)x;
	data->p_y += (int)y;
	return (0);
}

// data->d_x = cos(data->angle);
// data->d_y = sin(data->angle);
void	do_rays(t_data *data)
{
	float	x;
	float	y;
	float	angle;
	float	d_x;
	float	d_y;

	angle = data->angle - M_PI_4;
	ft_memset(data->rays->pixels, 0,
		data->map_->width * data->ts * data->map_->height * data->ts * sizeof(int));
	while (angle < data->angle + M_PI_4)
	{
		d_x = cos(angle);
		d_y = sin(angle);
		x = data->p_x;
		y = data->p_y;
		for (float i = 0; i < 100; i += 0.01)
		{
			if (!((x > 0 && x < data->map_->width * data->ts)
				&& (y > 0 && y < data->map_->height * data->ts)))
				break ;
			mlx_put_pixel(data->rays, x, y, 0x00FF00FF);
			x = x + d_x;
			y = y + d_y;
		}
		angle += 0.006544984694979;
	}
}

void	hook(void* param)
{
	t_data	*data;
	mlx_t	*mlx;

	data = param;
	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_R))
	{
		data->p_x = 2 * data->ts;
		data->p_y = 2 * data->ts;
	}
	player_speed(data);
	player_rotate(data);
	do_rays(data);
	data->p_img->instances[0].x = data->p_x - data->ps / 2;
	data->p_img->instances[0].y = data->p_y - data->ps / 2;
	printf("X: %f\tY: %f\tangle: %f\tdx: %f\tdy: %f\tfps: %f\n", data->p_x, data->p_y, data->angle, data->d_x, data->d_y, 1 / data->mlx->delta_time);
}

void	put_walls(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				mlx_image_to_window(data->mlx, data->walls, j * data->ts, i * data->ts);
			j++;
		}
		i++;
	}
}

int32_t	main(int argc, char **argv)
{
	t_data		data;
	t_map		map;

	if (parser(argc, argv, &map) != 0)
		return (1);
	if (init(&data, &map) != 0)
		return (1);
	put_walls(&data, data.map);
	mlx_image_to_window(data.mlx, data.p_img, data.p_x, data.p_y);
	mlx_key_hook(data.mlx, key_hook, &data);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
