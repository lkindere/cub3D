/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 20:48:25 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/21 22:39:14 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_line
{
	t_vec	p1;
	t_vec	p2;
	float	step;
}	t_line;

void	safe_pixel(mlx_image_t *image, t_vec vec, uint32_t color)
{
	if (vec.y > image->height || vec.x > image->width)
		return ;
	if (vec.x < 0 || vec.x > image->width - 0)
		return ;
	if (vec.y < 0 || vec.y > image->height - 0)
		return ;
	mlx_put_pixel(image, vec.x, vec.y, color);
}

void	draw_line_xy(mlx_image_t *image, t_line line, uint32_t color)
{
	while ((int)line.p1.x != (int)line.p2.x)
	{
		if (line.p1.x < line.p2.x)
			line.p1.x++;
		else if (line.p1.x > line.p2.x)
			line.p1.x--;
		if (line.p1.y < line.p2.y)
			line.p1.y += line.step;
		else if (line.p1.y > line.p2.y)
			line.p1.y -= line.step;
		safe_pixel(image, line.p1, color);
	}
}

void	draw_line_yx(mlx_image_t *image, t_line line, uint32_t color)
{
	while ((int)line.p1.y != (int)line.p2.y)
	{
		if (line.p1.y < line.p2.y)
			line.p1.y++;
		else if (line.p1.y > line.p2.y)
			line.p1.y--;
		if (line.p1.x < line.p2.x)
			line.p1.x += line.step;
		else if (line.p1.x > line.p2.x)
			line.p1.x -= line.step;
		safe_pixel(image, line.p1, color);
	}
}

//Draws a line from point 1 to point 2 using safe_pixel
void	draw_line(mlx_image_t *image, t_vec p1, t_vec p2, uint32_t color)
{
	t_vec	dist;
	t_line	line;

	line.p1 = p1;
	line.p2 = p2;
	dist.x = fabs(p1.x - p2.x);
	dist.y = fabs(p1.y - p2.y);
	if (fabs(p1.x) > 5000 || fabs(p1.y) > 5000
		|| fabs(p2.x) > 5000 || fabs(p2.y) > 5000)
		return ;
	if (dist.x >= dist.y)
	{
		line.step = dist.y / dist.x;
		draw_line_xy(image, line, color);
	}
	if (dist.x < dist.y)
	{
		line.step = dist.x / dist.y;
		draw_line_yx(image, line, color);
	}
	safe_pixel(image, p1, color);
	safe_pixel(image, p2, color);
}
