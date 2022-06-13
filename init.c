/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:23:47 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/13 15:29:07 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map && map->map[i])
		free(map->map[i++]);
	free(map->map);
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
}

void	init_map(t_map *map)
{
	map->map = malloc(sizeof(char *));
	if (!map->map)
		exit (0);
	map->map[0] = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->floor_color = 0;
	map->ceiling_color = 0;
	map->width = 0;
	map->height = 0;
	map->pos_x = 0;
	map->pos_y = 0;
	map->position = NONE;
	map->valid = VALID;
}
