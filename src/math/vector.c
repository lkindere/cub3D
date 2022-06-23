/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:58:23 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/23 16:00:55 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

//Returns the distance between 2 points
float	get_distance(t_vec p1, t_vec p2)
{
	return (sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2)));
}

//Adds 2 vectors
t_vec	add_vector(t_vec vec1, t_vec vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	return (vec1);
}

//Multiplies vector
t_vec	mult_vector(t_vec vec, float mult)
{
	vec.x *= mult;
	vec.y *= mult;
	return (vec);
}

//Returns a vector from x y
t_vec	vector(float x, float y)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

//Returns a vector from x y
t_vec_int	vector_int(int x, int y)
{
	t_vec_int	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}
