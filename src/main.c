/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:15:33 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/23 15:15:45 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				mlx_image_to_window(data->mlx, data->walls,
					j * data->tsm, i * data->tsm);
			j++;
		}
		i++;
	}
}

// void	resize(int32_t width, int32_t height, void* param)
// {
// 	t_data	*data;

// 	data = (t_data *)param;
// 	data->width = width;
// 	data->height = height;
// 	mlx_resize_image(data->p_img, width, height);
// 	mlx_resize_image(data->walls, width, height);
// 	mlx_resize_image(data->rays, width, height);
// 	mlx_resize_image(data->draw, width, height);
// }

int32_t	main(int argc, char **argv)
{
	t_data		data;
	t_map		map;

	if (parser(argc, argv, &map) != 0)
		return (1);
	if (init(&data, &map) != 0)
		return (1);
	put_walls(&data, data.map);
	mlx_image_to_window(data.mlx, data.p_img, data.player.x, data.player.y);
	mlx_key_hook(data.mlx, key_hook, &data);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_set_window_limit(data.mlx, data.mlx->width, data.mlx->height,
		data.mlx->width, data.mlx->height);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop(data.mlx);
	free_map(&map);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
