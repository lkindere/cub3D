/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 02:05:12 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/20 02:49:23 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays(t_data *data, t_ray r, t_vec start)
{
	float	max;
	float	height;
	t_vec	up;
	t_vec	down;

	max = sqrtf(powf(data->map_->width - 2, 2) + powf(data->map_->height - 2, 2));
	height = data->map_->height * ((r.distance / max) * -1 + 1);
	up = set_vector(start.x, start.y + height / 2 * data->ts);
	down = set_vector(start.x, start.y - height / 2 * data->ts);
	draw_line(data->draw, start, up, 0x00FF00FF);
	draw_line(data->draw, start, down, 0x00FF00FF);
}
