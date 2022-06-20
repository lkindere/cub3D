/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:58:40 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/20 11:25:05 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# define PI2 6.283185307179586

# include <math.h>

typedef struct s_vec
{
	float	x;
	float	y;
}	t_vec;

typedef struct s_vec_int
{
	int	x;
	int	y;
}	t_vec_int;

float	v_len(t_vec vec);
t_vec	v_norm(t_vec vec);
float	v_dot(t_vec a, t_vec b);

float		get_distance(t_vec p1, t_vec p2);
t_vec		vector(float x, float y);
t_vec_int	vector_int(int x, int y);

t_vec	add_vector(t_vec vec1, t_vec vec2);
t_vec	mult_vector(t_vec vec, float mult);

#endif