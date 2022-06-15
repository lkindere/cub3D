/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:15:33 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/15 02:09:44 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

int	walk = 5;
int	sprint = 10;
int	sneak = 1;

int	collision(t_data *data, int32_t x, int32_t y, char **map)
{
	int	step;
	int	ts;
	int	ps;

	step = data->speed;
	ts = data->ts;
	ps = data->ps;
	if (map[y / ts][x / ts] == '1'
		|| map[y / ts][(x + ps - 1) / ts] == '1'
		|| map[(y + ps - 1) / ts][x / ts] == '1'
		|| map[(y + ps - 1) / ts][(x + ps - 1) / ts] == '1')
		return (1);
	return (0);
}

void	draw_line(t_data *data)
{
	data->crosshair = mlx_new_image(data->mlx, 20, 20);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			mlx_put_pixel(data->crosshair, i, j, 0xFF00FF);
	}
	mlx_image_to_window(data->mlx, data->crosshair, data->p_x , data->p_y);
}

void	hook(void* param)
{
	t_data	*data;
	mlx_t	*mlx;
	char	**map;

	data = param;
	mlx = data->mlx;
	map = data->map;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_R))
	{
		data->p_x = 2 * data->ts;
		data->p_y = 2 * data->ts;
	}
	player_speed(data);
	player_rotate(data);
	data->p_img->instances[0].x = data->p_x;
	data->p_img->instances[0].y = data->p_y;
	data->crosshair->instances[0].x = data->p_x + 4 + data->d_x * 25;
	data->crosshair->instances[0].y = data->p_y + 4 + data->d_y * 25;
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
	draw_line(&data);
	mlx_key_hook(data.mlx, key_hook, &data);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
