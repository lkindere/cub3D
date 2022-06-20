/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:04:46 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/20 11:31:27 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_data(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	data->p_img = mlx_new_image(data->mlx, 16, 16);
	if (data->p_img == NULL)
		return (ERROR_MALLOC);
	ft_memset(data->p_img->pixels, 255,
		data->p_img->width * data->p_img->height * sizeof(int));
	data->speed = WALK;
	return (0);
}

void	copy_map(t_data *data, t_map *map)
{
	data->map = map->map;
	map->map = NULL;
	data->map_ = map;
	data->angle = data->map_->position * M_PI_2 * -1 + M_PI_2;
	data->dir = vector(cos(data->angle), sin(data->angle));
	data->player = vector(map->pos_x + 0.5, map->pos_y + 0.5);
	mlx_set_window_size(data->mlx, map->width * TS * 2, map->height * TS);
}

int	init_textures(t_data *data)
{
	data->textures.n = mlx_load_xpm42(data->map_->no);
	data->textures.s = mlx_load_xpm42(data->map_->so);
	data->textures.e = mlx_load_xpm42(data->map_->ea);
	data->textures.w = mlx_load_xpm42(data->map_->we);
	if (mlx_errno != 0)
	{
		printf("%s\n", mlx_strerror(mlx_errno));
		return (-1);
	}
	return (0);
}

int	init_walls(t_data *data)
{
	mlx_image_t	*walls;

	walls = mlx_new_image(data->mlx, 63, 63);
	if (walls == NULL)
		return (ERROR_MALLOC);
	ft_memset(walls->pixels, 180, walls->width * walls->height * sizeof(int));
	data->walls = walls;
	return (0);
}

int	init_rays(t_data *data, t_map *map)
{
	data->rays = mlx_new_image(data->mlx, map->width * TS, map->height * TS);
	if (data->rays == NULL)
		return (ERROR_MALLOC);
	mlx_image_to_window(data->mlx, data->rays, 0, 0);
	data->draw = mlx_new_image(data->mlx, map->width * TS, map->height * TS);
	if (data->draw == NULL)
		return (ERROR_MALLOC);
	mlx_image_to_window(data->mlx, data->draw, map->width * TS, 0);
	return (0);
}

int	init(t_data *data, t_map *map)
{
	if (init_data(data) != 0)
		return (1);
	copy_map(data, map);
	if (init_textures(data) != 0)
		return (2);
	if (init_walls(data) != 0)
		return (3);
	if (init_rays(data, map) != 0)
		return (4);
	screen_bounds(data->mlx->width, data->mlx->height);
	return (0);
}
