/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:23:47 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/12 20:24:02 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_map(t_map *map)
{
	map->map = NULL;
	map->NO = NULL;
	map->SO = NULL;
	map->WE = NULL;
	map->EA = NULL;
	map->floor_color = 0;
	map->ceiling_color = 0;
	map->width = 0;
	map->height = 0;
	map->valid = VALID;
}
