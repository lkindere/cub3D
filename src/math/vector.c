/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:58:23 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/18 14:56:13 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

/*
 *	Returns the length of the vector.
 */
float	v_len(t_vec vec)
{
	return (hypot(vec.x, vec.y));
}

/*
 *	Returns a normalized version of the input vector.
 *
 *	If length of the vector is 0, dodges division by 0 and returns input vector.
 */
t_vec	v_norm(t_vec vec)
{
	float	temp;
	t_vec	ret;

	temp = v_len(vec);
	if (temp != 0)
	{
		temp = 1 / temp;
		ret.x = vec.x * temp;
		ret.y = vec.y * temp;
		return (ret);
	}
	return (vec);
}

/*
 *	Returns the dot product of two vectors.
 *
 *	If the vectors are normalized, dot product is:
 *	1 if they point in the same direction,
 *	0 if they are orthogonal,
 *	-1 if they point in opposite directions.
 *
 *	If the vectors are normalised,
 *	the acos() of the dot product is the angle between the vectors.
 */
float	v_dot(t_vec a, t_vec b)
{
	return (sqrt(a.x * b.x + a.y + b.y));
}

//Returns a vector from x y
t_vec	set_vector(float x, float y)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

//Returns the distance between 2 points
float	get_distance(t_vec p1, t_vec p2)
{
	return (sqrtf(powf(p1.x - p2.x, 2) + powf(p1.y - p2.y, 2)));
}

//Returns a vector from x y
t_vec_int	set_vector_int(int x, int y)
{
	t_vec_int	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

//Normalizes a float vector to int value
void	vec_ftoi(t_vec *vec)
{
	vec->x = (int)vec->x;
	vec->y = (int)vec->y;
}
