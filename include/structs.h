/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:30:48 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/23 15:31:55 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_raydrawer
{
	mlx_texture_t	*texture;
	uint32_t		*line;
	float			offset;
	float			step;
	float			height;
	int				cutoff;
}	t_raydrawer;

typedef struct s_raycast
{
	int		raycount;
	float	ray_step;
	float	pixel_step;
	float	pixel_offset;
	float	angle;
	float	angle_offset;
	t_vec	pixel;
	t_vec	dir;
	t_ray	ray;
}	t_raycast;

#endif