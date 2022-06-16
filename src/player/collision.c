/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 05:49:20 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/16 06:16:13 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_data *data, int x, int y, char **map)
{
	if (data->p_y - data->ps / 2 + y < 2 
		|| data->p_y + data->ps / 2 + y > data->map_->height * 64 - 2)
		return (1);
	if (data->p_x - data->ps / 2 + x < 2 
		|| data->p_x + data->ps / 2 + x > data->map_->width * 64 - 2)
		return (1);
	if (map[((int)data->p_y - data->ps / 2 + y) / data->ts]
		[((int)data->p_x - data->ps / 2 + x)  / data->ts] == '1')
		return (1);
	if (map[((int)data->p_y + data->ps / 2 + y) / data->ts]
		[((int)data->p_x + data->ps / 2 + x)  / data->ts] == '1')
		return (1);
	if (map[((int)data->p_y + data->ps / 2 + y) / data->ts]
		[((int)data->p_x - data->ps / 2 + x)  / data->ts] == '1')
		return (1);
	if (map[((int)data->p_y - data->ps / 2 + y) / data->ts]
		[((int)data->p_x + data->ps / 2 + x)  / data->ts] == '1')
		return (1);
	return (0);
}

int check_collision(t_data *data, float x, float y)
{
	x = x * data->speed * (data->mlx->delta_time * 60);
	y = y * data->speed * (data->mlx->delta_time * 60);
	while (is_wall(data, 0, y, data->map) && (int)y != 0)
	{
		if ((int)y < 0)
			y++;
		if ((int)y > 0)
			y--;
	}
	while (is_wall(data, x, 0, data->map) && (int)x != 0)
	{
		if ((int)x < 0)
			x++;
		if ((int)x > 0)
			x--;
	}
	data->p_x += (int)x;
	data->p_y += (int)y;
	return (0);
}
