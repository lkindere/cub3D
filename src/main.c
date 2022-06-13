/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:15:33 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/14 01:14:26 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	walk = 5;
// int	step = 5;
int	sprint = 10;
int	sneak = 1;

int	collision(t_data *data, int32_t x, int32_t y, char **map)
{
	int	step;

	step = data->player->speed;
	
	if (map[(y - step) / 64][x / 64] == '1'
		|| map[(y - step) / 64][(x + 15) / 64] == '1')
		return (1);
	return (0);
}

void	move_up(t_data *data, t_player *player, mlx_instance_t *inst)
{
	if (collision(data, inst->x, inst->y, data->map))
		inst->y = (((inst->y - player->speed) / data->ts) + 1) * 64;
	else
		inst->y -= player->speed;
}

void	player_move(t_data *data, keys_t key, char **map)
{
	mlx_image_t	*player;
	int	x;
	int	y;

	player = data->player;
	x = player->instances[0].x;
	y = player->instances[0].y;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		move_up(data, data->player, &data->player->img->instances[0]);
		if (map[(y - step) / 64][x / 64] == '1'
			|| map[(y - step) / 64][(x + 15) / 64] == '1')
			player->instances[0].y = (((y - step) / 64) + 1) * 64;
		else
			player->instances[0].y -= step;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		if (map[(y + step + 16) / 64][x / 64] == '1'
			|| map[(y + step + 16) / 64][(x + 15) / 64] == '1')
			player->instances[0].y = (((y + step + 16) / 64)) * 64 - 16;
		else
			player->instances[0].y += step;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		if (map[y / 64][(x - step) / 64] == '1'
			|| map[(y + 15) / 64][(x - step) / 64] == '1')
			player->instances[0].x = (((x - step) / 64) + 1) * 64;
		else
			player->instances[0].x -= step;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		if (map[y / 64][(x + step + 16) / 64] == '1'
			|| map[(y + 15) / 64][(x + step + 16) / 64] == '1')
			player->instances[0].x = (((x + step + 16) / 64)) * 64 - 16;
		else
			player->instances[0].x += step;
	}

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
		data->player->img->instances[0].x = 1 * 64;
		data->player->img->instances[0].y = 1 * 64;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		step = sprint;
	else if (mlx_is_key_down(mlx, MLX_KEY_C))
		step = sneak;
	else
		step = walk;
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		player_move(data, MLX_KEY_UP, map);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		player_move(data, MLX_KEY_DOWN, map);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player_move(data, MLX_KEY_LEFT, map);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player_move(data, MLX_KEY_RIGHT, map);
	printf("X: %i\tY: %i\n", data->player->img->instances[0].x, data->player->img->instances[0].y);
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

	if (init(&data, argc, argv) != 0)
		return (1);
	put_walls(data->mlx, data->walls, data->map);
	mlx_image_to_window(data->mlx, data->player->img, 1 * 64, 1 * 64);
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
