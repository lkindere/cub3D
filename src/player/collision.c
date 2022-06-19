/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 05:49:20 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/20 01:44:28 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_data *data, float x, float y, char **map)
{
	if (data->p_y - data->ps / 2 + y < 1 
		|| data->p_y + data->ps / 2 + y > data->map_->height - 1)
		return (1);
	if (data->p_x - data->ps / 2 + x < 1 
		|| data->p_x + data->ps / 2 + x > data->map_->width - 1)
		return (1);
	if (map[(int)(data->p_y - data->ps / 2 + y)]
		[(int)(data->p_x - data->ps / 2 + x)] == '1')
		return (1);
	if (map[(int)(data->p_y + data->ps / 2 + y)]
		[(int)(data->p_x + data->ps / 2 + x)] == '1')
		return (1);
	if (map[(int)(data->p_y + data->ps / 2 + y)]
		[(int)(data->p_x - data->ps / 2 + x)] == '1')
		return (1);
	if (map[(int)(data->p_y - data->ps / 2 + y)]
		[(int)(data->p_x + data->ps / 2 + x)] == '1')
		return (1);
	return (0);
}

int	check_collision(t_data *data, float x, float y)
{
	x = x * data->speed * (data->mlx->delta_time * 60);
	y = y * data->speed * (data->mlx->delta_time * 60);
	while (y < 0 && is_wall(data, 0, y, data->map))
		y += 0.015625;
	while (y > 0 && is_wall(data, 0, y, data->map))
		y -= 0.015625;
	while (x < 0 && is_wall(data, x, y, data->map))
		x += 0.015625;
	while (x > 0 && is_wall(data, x, y, data->map))
		x -= 0.015625;
	data->p_x += x;
	data->p_y += y;
	return (0);
}
