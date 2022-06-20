/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 05:49:20 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/20 11:17:44 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_data *data, float x, float y, char **map)
{
	if (data->player.y - PS / 2 + y < 1 
		|| data->player.y + PS / 2 + y > data->map_->height - 1)
		return (1);
	if (data->player.x - PS / 2 + x < 1 
		|| data->player.x + PS / 2 + x > data->map_->width - 1)
		return (1);
	if (map[(int)(data->player.y - PS / 2 + y)]
		[(int)(data->player.x - PS / 2 + x)] == '1')
		return (1);
	if (map[(int)(data->player.y + PS / 2 + y)]
		[(int)(data->player.x + PS / 2 + x)] == '1')
		return (1);
	if (map[(int)(data->player.y + PS / 2 + y)]
		[(int)(data->player.x - PS / 2 + x)] == '1')
		return (1);
	if (map[(int)(data->player.y - PS / 2 + y)]
		[(int)(data->player.x + PS / 2 + x)] == '1')
		return (1);
	return (0);
}

int	check_collision(t_data *data, float x, float y)
{
	x = x * data->speed * (data->mlx->delta_time * 60);
	y = y * data->speed * (data->mlx->delta_time * 60);
	if (is_wall(data, x, y, data->map))
	{
		while (y < 0 && is_wall(data, 0, y, data->map))
			y += 0.015625;
		while (y > 0 && is_wall(data, 0, y, data->map))
			y -= 0.015625;
		while (x < 0 && is_wall(data, x, y, data->map))
			x += 0.015625;
		while (x > 0 && is_wall(data, x, y, data->map))
			x -= 0.015625;
	}
	data->player.x += x;
	data->player.y += y;
	return (0);
}
