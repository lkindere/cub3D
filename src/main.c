/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:15:33 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/12 16:26:44 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define WIDTH 1280
#define HEIGHT 720

mlx_image_t	*g_img;

void	player_move(mlx_image_t *player, keys_t key, char **map)
{
	int	x;
	int	y;

	x = player->instances[0].x;
	y = player->instances[0].y;
	if (key == MLX_KEY_UP)
	{
		if (map[(y - 5) / 64][x / 64] == '1'
			|| map[(y - 5) / 64][(x + 15) / 64] == '1')
			player->instances[0].y = (((y - 5) / 64) + 1) * 64;
		else
			player->instances[0].y -= 5;
	}
	if (key == MLX_KEY_DOWN)
	{
		if (map[(y + 5 + 16) / 64][x / 64] == '1'
			|| map[(y + 5 + 16) / 64][(x + 15) / 64] == '1')
			player->instances[0].y = (((y + 5 + 16) / 64)) * 64 - 16;
		else
			player->instances[0].y += 5;
	}
	if (key == MLX_KEY_LEFT)
	{
		if (map[y / 64][(x - 5) / 64] == '1'
			|| map[(y + 15) / 64][(x - 5) / 64] == '1')
			player->instances[0].x = (((x - 5) / 64) + 1) * 64;
		else
			player->instances[0].x -= 5;
	}
	if (key == MLX_KEY_RIGHT)
	{
		if (map[y / 64][(x + 5 + 16) / 64] == '1'
			|| map[(y + 15) / 64][(x + 5 + 16) / 64] == '1')
			player->instances[0].x = (((x + 5 + 16) / 64)) * 64 - 16;
		else
			player->instances[0].x += 5;
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
		g_img->instances[0].x = 1 * 64;
		g_img->instances[0].y = 1 * 64;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		player_move(g_img, MLX_KEY_UP, map);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		player_move(g_img, MLX_KEY_DOWN, map);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player_move(g_img, MLX_KEY_LEFT, map);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player_move(g_img, MLX_KEY_RIGHT, map);
	printf("X: %i\tY: %i\n", g_img->instances[0].x, g_img->instances[0].y);
}

void	get_map(char ***map, char **argv)
{
	int	fd;
	char	*line;
	char	*buff;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	buff = NULL;
	while (line)
	{
		ft_add_str(&buff, line);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	*map = ft_split(buff, '\n');
	free(buff);
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
	mlx_t		*mlx;
	mlx_image_t	*walls;
	char		**map;

	printf("works\n");
	if (argc != 2 || !argv[1])
		return (1);
	get_map(&map, argv);
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	data = ft_calloc(1, sizeof(t_data));
	if (!mlx || !data)
		exit(EXIT_FAILURE);
	data->mlx = mlx;
	data->map = map;
	g_img = mlx_new_image(mlx, 16, 16);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	walls = mlx_new_image(mlx, 64, 64);
	memset(walls->pixels, 180, walls->width * walls->height * sizeof(int));
	put_walls(mlx, walls, map);
	mlx_image_to_window(mlx, g_img, 1 * 64, 1 * 64);
	mlx_loop_hook(mlx, &hook, data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
