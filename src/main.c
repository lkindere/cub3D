/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:15:33 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/14 23:14:23 by lkindere         ###   ########.fr       */
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

	step = data->player->speed;
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
	data->player->crosshair = mlx_new_image(data->mlx, 10, 10);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			mlx_put_pixel(data->player->crosshair, i, j, 3093151);
	}
	mlx_image_to_window(data->mlx, data->player->crosshair, data->player->img->instances[0].x , data->player->img->instances[0].y);
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
		data->player->img->instances[0].x = 2 * data->ts;
		data->player->img->instances[0].y = 2 * data->ts;
	}
	player_speed(data);
	player_move(data);
	player_rotate(data);
	data->player->crosshair->instances[0].x = data->player->img->instances[0].x + data->player->dx * 50;
	data->player->crosshair->instances[0].y = data->player->img->instances[0].y + data->player->dy * 50;
	printf("X: %i\tY: %i\tangle: %f\tdx: %f\tdy: %f\n", data->player->img->instances[0].x, data->player->img->instances[0].y, data->player->angle, data->player->dx, data->player->dy);
}

void	put_walls(mlx_t *mlx, mlx_image_t *walls, char **map)
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
				mlx_image_to_window(mlx, walls, j * 64, i * 64);
			j++;
		}
		i++;
	}
}

int32_t	main(int argc, char **argv)
{
	t_data		*data;
	t_map		map;

	if (parser(argc, argv, &map) != 0)
		return (1);
	if (init(&data, argc, argv) != 0)
		return (1);
	data->map = map.map;
	put_walls(data->mlx, data->walls, data->map);
	mlx_image_to_window(data->mlx, data->player->img, 1 * 64, 1 * 64);
	draw_line(data);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
