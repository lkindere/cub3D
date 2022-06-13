/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:18:21 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/13 18:21:01 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		step = sprint;
	else if (mlx_is_key_down(mlx, MLX_KEY_C))
		step = sneak;
	else
		step = walk;
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