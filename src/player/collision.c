/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 05:49:20 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/17 04:07:57 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	is_wall(t_data *data, int x, int y, char **map)
// {
// 	if (data->p_y - data->ps / 2 + y < 1 
// 		|| data->p_y + data->ps / 2 + y > data->map_->height * 64 - 1)
// 		return (1);
// 	if (data->p_x - data->ps / 2 + x < 1 
// 		|| data->p_x + data->ps / 2 + x > data->map_->width * 64 - 1)
// 		return (1);
// 	// printf("Y: %d, X: %d\n", (int)((data->p_y - data->ps / 2 + y) / data->ts), (int)((data->p_x - data->ps / 2 + x)  / data->ts));
// 	// printf("Y: %d, X: %d\n", (int)((data->p_y + data->ps / 2 + y) / data->ts), (int)((data->p_x + data->ps / 2 + x)  / data->ts));
// 	// printf("Y: %d, X: %d\n", (int)((data->p_y + data->ps / 2 + y) / data->ts), (int)((data->p_x - data->ps / 2 + x)  / data->ts));
// 	// printf("Y: %d, X: %d\n", (int)((data->p_y - data->ps / 2 + y) / data->ts), (int)((data->p_x + data->ps / 2 + x)  / data->ts));
// 	if (map[(int)((data->p_y - data->ps / 2 + y) / data->ts)]
// 		[(int)((data->p_x - data->ps / 2 + x)  / data->ts)] == '1')
// 		return (1);
// 	if (map[(int)((data->p_y + data->ps / 2 + y) / data->ts)]
// 		[(int)((data->p_x + data->ps / 2 + x)  / data->ts)] == '1')
// 		return (1);
// 	if (map[(int)((data->p_y + data->ps / 2 + y) / data->ts)]
// 		[(int)((data->p_x - data->ps / 2 + x)  / data->ts)] == '1')
// 		return (1);
// 	if (map[(int)((data->p_y - data->ps / 2 + y) / data->ts)]
// 		[(int)((data->p_x + data->ps / 2 + x)  / data->ts)] == '1')
// 		return (1);
// 	// printf("^No collision\n");
// 	return (0);
// }

int	check_collision(t_data *data, float x, float y)
{
	x = x * data->speed * (data->mlx->delta_time * 60);
	y = y * data->speed * (data->mlx->delta_time * 60);
	// printf("X: %d, Y: %d\n", (int)x, (int)y);
	// while (is_wall(data, 0, y, data->map) && (int)y != 0)
	// {
	// 	if ((int)y < 0)
	// 		y++;
	// 	if ((int)y > 0)
	// 		y--;
	// }
	// while (is_wall(data, x, y, data->map) && (int)x != 0)
	// {
	// 	if ((int)x < 0)
	// 		x++;
	// 	if ((int)x > 0)
	// 		x--;
	// }
	// printf("Adding X: %d, Y: %d\n", (int)x, (int)y);
	data->p_x += x;
	data->p_y += y;
	return (0);
}
