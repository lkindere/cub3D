/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 05:49:20 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/20 01:29:31 by lkindere         ###   ########.fr       */
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
	while (is_wall(data, 0, y, data->map))
	{
		if (y < 0)
		{
			y += 0.015625;
			if (y >= 0)
				break ;
		}
		if (y > 0)
		{
			y -= 0.015625;
			if (y <= 0)
				break ;
		}
	}
	while (is_wall(data, x, y, data->map))
	{
		if (x < 0)
		{
			x += 0.015625;
			if (x >= 0)
				break ;
		}
		if (x > 0)
		{
			x -= 0.015625;
			if (x <= 0)
				break ;
		}
	}
	data->p_x += x;
	data->p_y += y;
	return (0);
}












// int	is_wall(char **map, int x, int y)
// {
// 	if (map[y][x] == '1' || map[y][x] == 0)
// 		return (1);
// 	return (0);
// }

// // int	check_collision(t_data *data, float x, float y)
// // {
// // 	t_vec	player;
// // 	t_vec	dir;
// // 	float	speed;

// // 	speed = data->speed * (data->mlx->delta_time * 60);
// // 	player = set_vector(data->p_x, data->p_y);
// // 	dir = set_vector(player.x + x * speed, player.y + y * speed);
// // 	if (data->map[(int)player.y][(int)dir.x] != '1' && data->map[(int)player.y][(int)dir.x] != 0) //Can move in y
// // 		data->p_x = dir.x;
// // 	if (data->map[(int)dir.y][(int)player.x] != '1' && data->map[(int)dir.y][(int)player.x] != 0) //Can move in y
// // 		data->p_y = dir.y;
// // }

// int	check_collision(t_data *data, float x, float y)
// {
// 	t_vec	offset;
// 	t_vec	player;
// 	t_vec	dir;
// 	float	speed;

// 	offset = set_vector(data->ps / 2, data->ps /2);
// 	if (x < 0)
// 		offset.x *= -1;
// 	if (y < 0)
// 		offset.y *= -1;
// 	speed = data->speed * (data->mlx->delta_time * 60);
// 	player = set_vector(data->p_x, data->p_y);
// 	dir = set_vector(player.x + x * speed, player.y + y * speed);
// 	if (!is_wall(data->map, dir.x + offset.x, dir.y + offset.y))
// 	{
// 		data->p_x = dir.x;
// 		data->p_y = dir.y;
// 	}

// }
