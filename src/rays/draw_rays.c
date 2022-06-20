/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 02:05:12 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/20 10:19:10 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays(t_data *data, t_ray r, t_vec start)
{
	float	height;
	t_vec	up;
	t_vec	down;

	height = 1.0 / r.distance * data->map_->height * 2;
	up = set_vector(start.x, start.y + height / 2 * data->ts);
	down = set_vector(start.x, start.y - height / 2 * data->ts);
	draw_line(data->draw, start, up, 0x00FF00FF);
	draw_line(data->draw, start, down, 0x00FF00FF);
}
