/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:15:33 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/16 06:48:40 by mmeising         ###   ########.fr       */
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
