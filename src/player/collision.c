/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 05:49:20 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/19 02:59:17 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_data *data, t_vec point)
{
	char		**map;
	t_vec_int	tl;
	t_vec_int	tr;
	t_vec_int	bl;
	t_vec_int	br;

	map = data->map;
	printf("Player: %f, %f\n", data->p_x, data->p_y);
	printf("Playe size: %f\n", data->ps);
	printf("Point X: %f, Y: %f\n", point.x, point.y);
	tl = set_vector_int(point.x - data->ps / 2, point.y - data->ps / 2);
	tr = set_vector_int(point.x + data->ps / 2, point.y - data->ps / 2);
	bl = set_vector_int(point.x - data->ps / 2, point.y + data->ps / 2);
	br = set_vector_int(point.x + data->ps / 2, point.y + data->ps / 2);
	printf("TL: %d, %d\n", tl.x, tl.y);
	printf("TR: %d, %d\n", tr.x, tr.y);
	printf("BL: %d, %d\n", bl.x, bl.y);
	printf("BR: %d, %d\n", br.x, br.y);
	if (map[tl.y][tl.x] == '1')
	{
		printf("Collision 1\n");
		return (1);
	}
	if (map[tr.y][tr.x] == '1')
	{
		printf("Collision 2\n");
		return (1);
	}
	if (map[bl.y][bl.x] == '1')
	{
		printf("Collision 3\n");
		return (1);
	}
	if (map[br.y][br.x] == '1')
	{
		printf("Collision 4\n");
		return (1);
	}
	return (0);
}

int	check_collision(t_data *data, float x, float y)
{
	t_vec_int	map;
	t_vec_int	step;
	t_vec		player;
	t_vec		dir;
	float		speed;

	step = set_vector_int(0, 0);
	speed = data->speed * (data->mlx->delta_time * 60);
	player = set_vector(data->p_x, data->p_y);
	dir = set_vector(player.x + x * speed, player.y + y * speed);
	map = set_vector_int(dir.x, dir.y);
	if (x < 0.01)
		step.x = 1;
	if (x > 0.01)
		step.x = -1;
	if (y < 0.01)
		step.y = 1;
	if (y > 0.01)
		step.y = -1;
	if (!is_wall(data, set_vector(dir.x, dir.y)))
	{
		data->p_x = dir.x + 0.01 * step.x;
		data->p_y = dir.y + 0.01 * step.y;
		return (0);
	}
	else if (!is_wall(data, set_vector(dir.x + step.x, dir.y)))
	{
		data->p_y = dir.y;
		if (step.x > 0)
			data->p_x = (int)data->p_x + (data->ps / 2 + 0.01);
		if (step.x < 0)
			data->p_x = (int)data->p_x + 1 - (data->ps / 2 + 0.01);
	}
	else if (!is_wall(data, set_vector(dir.x, dir.y + step.y)))
	{
		data->p_x = dir.x;
		if (step.y > 0)
			data->p_y = (int)data->p_y + (data->ps / 2 + 0.01);
		if (step.y < 0)
			data->p_y = (int)data->p_y + 1 - (data->ps / 2 + 0.01);
	}
}
