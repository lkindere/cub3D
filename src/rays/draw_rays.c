/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 02:05:12 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/21 02:40:03 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef	struct	s_raydrawer
{
	mlx_texture_t	*texture;
	uint32_t		*line;
	float			pixel;
	float			offset;
	float			step;
	float			height;
}	t_raydrawer;

uint32_t	*split_line(mlx_texture_t *texture, int pixel)
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
	pixel *= bpp;
	size = texture->width * texture->height * bpp;
	while (pixel < size)
	{
		rgb[0] = texture->pixels[pixel];
		rgb[1] = texture->pixels[pixel + 1];
		rgb[2] = texture->pixels[pixel + 2];
		rgb[3] = texture->pixels[pixel + 3];
		line[++i] = (rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + rgb[3];
		pixel += 64 * bpp;
	}
	return (line);
}

static void	set_texture(t_textures textures, t_raydrawer *rd, t_ray *r)
{
	rd->texture = NULL;
	if (r->hit_pos == N || r->hit_pos == S)
	{
		rd->pixel = (int)((r->hit.x - (int)r->hit.x) * TS);
		if (r->hit_pos == N)
			rd->texture = &textures.n->texture;
		if (r->hit_pos == S)
			rd->texture = &textures.s->texture;
		return ;
	}
	if (r->hit_pos == E || r->hit_pos == W)
	{
		rd->pixel = (int)((r->hit.y - (int)r->hit.y) * TS);
		if (r->hit_pos == E)
			rd->texture = &textures.e->texture;
		if (r->hit_pos == W)
			rd->texture = &textures.w->texture;
	}
}

void	draw_rays(t_data *data, t_ray *r, t_vec start)
{
	t_raydrawer	rd;
	int			index;

	set_texture(data->textures, &rd, r);
	rd.height = 1.0 / r->distance * HEIGHT;
	rd.step = TS / rd.height;
	index = TS / 2;
	rd.offset = 0;
	rd.line = split_line(rd.texture, rd.pixel);
	for (int i = 0; i < rd.height / 2; i++)
	{
		safe_pixel(data->draw, vector(start.x, HEIGHT / 2 - i), rd.line[index - (int)rd.offset]);
		safe_pixel(data->draw, vector(start.x, HEIGHT / 2 + i), rd.line[index + (int)rd.offset]);
		rd.offset += rd.step;
	}
}
