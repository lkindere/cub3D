/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:04:46 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/14 18:08:07 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_data(t_data **data, int argc, char **argv)
{
	if (argc != 2 || !argv[1])
		return (1);
	*data = ft_calloc(1, sizeof(t_data));
	if (!*data)
		return (ERROR_MALLOC);
	(*data)->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	// get_map(&(*data)->map, argv);
	(*data)->ts = 64;
	(*data)->ps = 16;
	return (0);
}

int	init_player(t_data *data)
{
	t_player	*player;
	mlx_image_t	*img;

	player = ft_calloc(1, sizeof(t_player));
	if (player == NULL)
		return (ERROR_MALLOC);
	player->img = mlx_new_image(data->mlx, 16, 16);
	if (player == NULL)
		return (ERROR_MALLOC);
	img = player->img;
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int));
	player->speed = WALK;
	data->player = player;
	return (0);
}

int	init_walls(t_data *data)
{
	mlx_image_t	*walls;

	walls = mlx_new_image(data->mlx, 64, 64);
	if (walls == NULL)
		return (ERROR_MALLOC);
	ft_memset(walls->pixels, 180, walls->width * walls->height * sizeof(int));
	data->walls = walls;
	return (0);
}

int	init(t_data **data, int argc, char **argv)
{
	if (init_data(data, argc, argv) != 0)
		return (1);
	if (init_player(*data) != 0)
		return (2);
	if (init_walls(*data) != 0)
		return (3);
	if (init_player(*data) != 0)
		return (4);
	return (0);
}
