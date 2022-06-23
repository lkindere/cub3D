/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:23:57 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/23 14:39:50 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//1 Toggles minimap rays 	[1]
//2	Toggles mouse on/off 	[2]
//3 Toggles funky ceilings	[4]
//4 Toggles funky floors	[8]
//5 Toggles animated walls	[16]
void	set_effects(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		data->effects ^= 1;
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
		data->effects ^= 2;
	if (keydata.key == MLX_KEY_3 && keydata.action == MLX_PRESS)
		data->effects ^= 4;
	if (keydata.key == MLX_KEY_4 && keydata.action == MLX_PRESS)
		data->effects ^= 8;
	if (keydata.key == MLX_KEY_5 && keydata.action == MLX_PRESS)
		data->effects ^= 16;
}

uint32_t	funky_stuff(unsigned int color)
{
	return (color + (rand() % 255));
}
