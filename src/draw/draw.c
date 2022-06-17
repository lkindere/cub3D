/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 20:48:25 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/17 21:37:01 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_line
{
	t_vec	p1;
	t_vec	p2;
	float	step;
}	t_line;

//Sets or gets screen max bounds for safe drawing
t_vec_int	screen_bounds(int x, int y)
{
	static t_vec_int bounds;

	if (x > -1 || y > -1)
	{
		bounds.x = x;
		bounds.y = y;
	}
	return (bounds);
}

void safe_pixel(mlx_image_t *image, t_vec vec, uint32_t color)
{
	t_vec_int	bounds;

	bounds = screen_bounds(-1, -1);
	if (vec.x < 1 || vec.x > bounds.x)
		return ;
	if (vec.y < 1 || vec.y > bounds.y)
		return ;
	mlx_put_pixel(image, vec.x, vec.y, color);
}

void	draw_line_xy(mlx_image_t *image, t_line line, uint32_t color)
{
	int i;

	i = 0;
	while ((line.p1.x != line.p2.x || line.p1.y != line.p2.y) && ++i)
	{
		if (line.p1.x < line.p2.x)
			line.p1.x++;
		if (line.p1.x > line.p2.x)
			line.p1.x--;
		if (line.step * i >= 1)
		{
			if (line.p1.y < line.p2.y)
				line.p1.y++;
			if (line.p1.y > line.p2.y)
				line.p1.y--;
			i = 0;
		}
		safe_pixel(image, line.p1, color);
	}
}

void	draw_line_yx(mlx_image_t *image, t_line line, uint32_t color)
{
	int	i;

	i = 0;
	while ((line.p1.x != line.p2.x || line.p1.y != line.p2.y) && ++i)
	{
		if (line.p1.y < line.p2.y)
			line.p1.y++;
		if (line.p1.y > line.p2.y)
			line.p1.y--;
		if (line.step * i >= 1)
		{
			if (line.p1.x < line.p2.x)
				line.p1.x++;;
			if (line.p1.x > line.p2.x)
				line.p1.x--;
			i = 0;
		}
		safe_pixel(image, line.p1, color);
	}
}

//Draws a line from point 1 to point 2 using safe_pixel
void	draw_line(mlx_image_t *image, t_vec p1, t_vec p2, uint32_t color)
{
	int		i;
	t_vec	dist;
	t_line	line;

	i = -1;
	vec_ftoi(&p1);
	vec_ftoi(&p2);
	line.p1 = p1;
	line.p2 = p2;
	dist.x = abs(p1.x - p2.x);
	dist.y = abs(p1.y - p2.y);
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
