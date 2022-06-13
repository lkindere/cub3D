/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:58:40 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/14 00:00:02 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include <math.h>

typedef struct s_vec
{
	float	x;
	float	y;
}	t_vec;

float	v_len(t_vec vec);
t_vec	v_norm(t_vec vec);
float	v_dot(t_vec a, t_vec b);

#endif