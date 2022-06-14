/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:54:35 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/15 00:54:11 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_data *data, int step)
{
	if (collision(data, data->p_x, data->p_y - step, data->map))
	{
		while (step > data->ts
			&& collision(data, data->p_x, data->p_y - step, data->map))
			step -= data->ts;
		data->p_y = (((data->p_y - step) / data->ts) + 1) * data->ts;
	}
	else
		data->p_y -= step;
}

void	move_down(t_data *data, int step)
{
	if (collision(data, data->p_x, data->p_y + step, data->map))
	{
		while (step > data->ts && collision(data, data->p_x, data->p_y + step, data->map))
			step -= data->ts;
		data->p_y = ((data->p_y + step + data->ps) / data->ts) * data->ts - data->ps;
	}
	else
		data->p_y += step;
}

void	move_left(t_data *data, int step)
{
	if (collision(data, data->p_x - step, data->p_y, data->map))
	{
		while (step > data->ts && collision(data, data->p_x - step, data->p_y, data->map))
			step -= data->ts;
		data->p_x = (((data->p_x - step) / data->ts) + 1) * data->ts;
	}
	else
		data->p_x -= step;
}

void	move_right(t_data *data, int step)
{
	if (collision(data, data->p_x + step, data->p_y, data->map))
	{
		while (step > data->ts && collision(data, data->p_x + step, data->p_y, data->map))
			step -= data->ts;
		data->p_x = ((data->p_x + step + data->ps) / data->ts) * data->ts - data->ps;
	}
	else
		data->p_x += step;
}
