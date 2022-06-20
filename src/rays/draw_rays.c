/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 02:05:12 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/20 18:29:04 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	*split_line(mlx_texture_t *texture, int index)
{
	int			i;
	int			bpp;
	int			size;
	uint8_t		rgb[4];
	uint32_t	*line;

	i = -1;
	bpp = texture->bytes_per_pixel;
	line = malloc(sizeof(uint32_t) * 64);
	if (!line)
		return (NULL);
	index *= bpp;
	size = texture->width * texture->height * bpp;
	while (index < size)
	{
		rgb[0] = texture->pixels[index];
		rgb[1] = texture->pixels[index + 1];
		rgb[2] = texture->pixels[index + 2];
		rgb[3] = texture->pixels[index + 3];
		line[++i] = (rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + rgb[3];
		index += 64 * bpp;
	}
	return (line);
}

void	draw_rays(t_data *data, t_ray r, t_vec start)
{
	uint32_t	*line;
	int			index;
	float		offset;
	float		step;
	float		height;

	height = 1.0 / r.distance * HEIGHT;
	if (height > HEIGHT)
		height = HEIGHT;
	step = TS / height;
	index = TS / 2;
	offset = 0;
	line = split_line(&data->textures.n->texture, 50);
	for (int i = 0; i < height / 2; i++)
	{
		safe_pixel(data->draw, vector(start.x, HEIGHT / 2 - i), line[index - (int)offset]);
		safe_pixel(data->draw, vector(start.x, HEIGHT / 2 + i), line[index + (int)offset]);
		offset += step;
	}
}
