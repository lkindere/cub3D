/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:04:46 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/23 15:13:26 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_data(t_data *data, t_map *map)
{
	data->mouse = vector(-1, -1);
	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	data->tsm = WIDTH * MM / (map->height + map->width / 2.0);
	while (data->tsm * PS < 1)
		data->tsm++;
	data->p_img = mlx_new_image(data->mlx, (data->tsm * PS), (data->tsm * PS));
	if (data->p_img == NULL)
		return (ERROR_MALLOC);
	ft_memset(data->p_img->pixels, 255,
		data->p_img->width * data->p_img->height * sizeof(int));
	data->speed = WALK;
	data->width = 1024;
	data->height = 768;
	return (0);
}

static void	copy_map(t_data *data, t_map *map)
{
	data->map = map->map;
	map->map = NULL;
	data->map_ = map;
	data->angle = data->map_->position * M_PI_2;
	data->dir = vector(cos(data->angle), sin(data->angle));
	data->player = vector(map->pos_x + 0.5, map->pos_y + 0.5);
	mlx_set_window_size(data->mlx, data->width, data->height);
}

static int	init_textures(t_data *data)
{
	int	i;

	i = 0;
	data->textures.n = mlx_load_xpm42(data->map_->no);
	data->textures.s = mlx_load_xpm42(data->map_->so);
	data->textures.e = mlx_load_xpm42(data->map_->ea);
	data->textures.w = mlx_load_xpm42(data->map_->we);
	while (data->map_->door_text && data->map_->door_text[i])
		i++;
	data->textures.door = malloc(sizeof(xpm_t *) * (i + 1));
	if (!data->textures.door)
		return (ERROR_MALLOC);
	i = 0;
	while (data->map_->door_text && data->map_->door_text[i])
	{
		data->textures.door[i] = mlx_load_xpm42(data->map_->door_text[i]);
		i++;
	}
	data->textures.door[i] = NULL;
	if (mlx_errno != 0)
		return (-1);
	return (0);
}

static int	init_images(t_data *data)
{
	data->walls = mlx_new_image(data->mlx, data->tsm, data->tsm);
	if (data->walls == NULL)
		return (ERROR_MALLOC);
	ft_memset(data->walls->pixels, 180,
		data->walls->width * data->walls->height * sizeof(int));
	data->rays = mlx_new_image(data->mlx,
			data->map_->width * data->tsm, data->map_->height * data->tsm);
	if (data->rays == NULL)
		return (ERROR_MALLOC);
	mlx_image_to_window(data->mlx, data->rays, 0, 0);
	mlx_set_instance_depth(&data->rays->instances[0], 5);
	data->draw = mlx_new_image(data->mlx, data->width, data->height);
	if (data->draw == NULL)
		return (ERROR_MALLOC);
	mlx_image_to_window(data->mlx, data->draw, 0, 0);
	return (0);
}

int	init(t_data *data, t_map *map)
{
	if (init_data(data, map) != 0)
		return (1);
	copy_map(data, map);
	if (init_textures(data) != 0)
		return (2);
	if (init_images(data) != 0)
		return (3);
	return (0);
}
