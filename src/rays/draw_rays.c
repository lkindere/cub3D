/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 02:05:12 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/21 00:13:47 by lkindere         ###   ########.fr       */
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

mlx_texture_t	*set_texture(t_textures textures, t_ray r, float *pixel)
{
	mlx_texture_t	*texture;

	texture = NULL;
	if (r.hit_pos == N || r.hit_pos == S)
	{
		*pixel = (int)((r.hit.x - (int)r.hit.x) * TS);
		if (r.hit_pos == N)
			texture = &textures.n->texture;
		if (r.hit_pos == S)
			texture = &textures.s->texture;
		return (texture);
	}
	if (r.hit_pos == E || r.hit_pos == W)
	{
		*pixel = (int)((r.hit.y - (int)r.hit.y) * TS);
		if (r.hit_pos == E)
			texture = &textures.e->texture;
		if (r.hit_pos == W)
			texture = &textures.w->texture;
	}
	return (texture);
}

void	draw_rays(t_data *data, t_ray r, t_vec start)
{
	mlx_texture_t	*texture;
	uint32_t		*line;
	int				index;
	float			pixel;
	float			offset;
	float			step;
	float			height;

	texture = set_texture(data->textures, r, &pixel);
	height = 1.0 / r.distance * HEIGHT;
	step = TS / height;
	index = TS / 2;
	offset = 0;
	line = split_line(texture, pixel);
	for (int i = 0; i < height / 2; i++)
	{
		safe_pixel(data->draw, vector(start.x, HEIGHT / 2 - i), line[index - (int)offset]);
		safe_pixel(data->draw, vector(start.x, HEIGHT / 2 + i), line[index + (int)offset]);
		offset += step;
	}
}
