/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 02:05:12 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/23 08:03:25 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_raydrawer
{
	mlx_texture_t	*texture;
	uint32_t		*line;
	float			offset;
	float			step;
	float			height;
	int				cutoff;
}	t_raydrawer;

static int	split_line(uint32_t **line, mlx_texture_t *texture, int pixel)
{
	int			i;
	int			bpp;
	int			size;
	uint8_t		rgb[4];

	i = -1;
	bpp = texture->bytes_per_pixel;
	*line = malloc(sizeof(uint32_t) * 64);
	if (!(*line))
		return (ERROR_MALLOC);
	pixel *= bpp;
	size = texture->width * texture->height * bpp;
	while (pixel < size)
	{
		rgb[0] = texture->pixels[pixel];
		rgb[1] = texture->pixels[pixel + 1];
		rgb[2] = texture->pixels[pixel + 2];
		rgb[3] = texture->pixels[pixel + 3];
		(*line)[++i] = (rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + rgb[3];
		pixel += 64 * bpp;
	}
	return (0);
}

mlx_texture_t	*get_door(t_textures *textures)
{
	uint32_t	time;

	time = mlx_get_time() % 4;
	if (time == 0)
		return (&textures->door1->texture);
	if (time == 1)
		return (&textures->door2->texture);
	if (time == 2)
		return (&textures->door3->texture);
	if (time == 3)
		return (&textures->door4->texture);
}

static int	set_texture(t_textures *textures, t_raydrawer *rd, t_ray *r)
{
	int	pixel;

	if (r->hit_pos == N || r->hit_pos == S)
	{
		pixel = ((r->hit.x - (int)r->hit.x) * TS);
		if (r->hit_pos == N)
			rd->texture = &textures->n->texture;
		if (r->hit_pos == S)
			rd->texture = &textures->s->texture;
		if (r->is_door)
			rd->texture = get_door(textures);
		return (split_line(&rd->line, rd->texture, pixel));
	}
	if (r->hit_pos == E || r->hit_pos == W)
	{
		pixel = ((r->hit.y - (int)r->hit.y) * TS);
		if (r->hit_pos == E)
			rd->texture = &textures->e->texture;
		if (r->hit_pos == W)
			rd->texture = &textures->w->texture;
		if (r->is_door)
			rd->texture = get_door(textures);
	}

	return (split_line(&rd->line, rd->texture, pixel));
}

static void	set_params(t_data *data, t_raydrawer *rd, t_ray *r)
{
	rd->offset = 0;
	rd->height = 1.0 / r->distance * HEIGHT;
	rd->step = TS / rd->height;
	rd->cutoff = (HEIGHT - rd->height) / 2;
	if (rd->cutoff < 0)
	{
		rd->offset = rd->step * -rd->cutoff;
		rd->cutoff = 0;
	}
}

int	draw_rays(t_data *data, t_ray *r, t_vec start)
{
	int			i;
	t_raydrawer	rd;

	if (set_texture(&data->textures, &rd, r) != 0)
		return (ERROR_MALLOC);
	set_params(data, &rd, r);
	i = rd.cutoff - 1;
	while (++i < HEIGHT - rd.cutoff && rd.offset < TS)
	{
		safe_pixel(data->draw, vector(start.x, i),
			rd.line[(int)rd.offset]);
		rd.offset += rd.step;
	}
	free(rd.line);
	return (0);
}


// void	draw_rays(t_data *data, t_ray *r, t_vec start)
// {
// 	int			i;
// 	int			index;
// 	t_raydrawer	rd;

// 	i = -1;
// 	set_texture(data->textures, &rd, r);
// 	rd.height = 1.0 / r->distance * HEIGHT;
// 	rd.step = TS / rd.height;
// 	index = TS / 2;
// 	rd.offset = 0;
// 	rd.line = split_line(rd.texture, rd.pixel);
// 	if (rd.height > HEIGHT)
// 		rd.height = HEIGHT;
// 	while (++i < rd.height / 2)
// 	{
// 		safe_pixel(data->draw, vector(start.x, HEIGHT / 2 - i),
// 			rd.line[index - (int)rd.offset]);
// 		safe_pixel(data->draw, vector(start.x, HEIGHT / 2 + i),
// 			rd.line[index + (int)rd.offset]);
// 		rd.offset += rd.step;
// 	}
// 	free(rd.line);
// }
