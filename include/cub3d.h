/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 00:47:44 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/12 03:54:54 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/MLX42/include/MLX42/MLX42.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <fcntl.h>

typedef struct s_data
{
	char	**map;
	mlx_t	*mlx;
}	t_data;

int	ft_add_char(char **str, char c);
int	ft_add_str(char **str, char *add);
