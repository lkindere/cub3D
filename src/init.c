/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:04:46 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/14 00:45:10 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map(char ***map, char **argv)
{
	int	fd;
	char	*line;
	char	*buff;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	buff = NULL;
	while (line)
	{
		ft_add_str(&buff, line);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	*map = ft_split(buff, '\n');
	free(buff);
}

int	init_data(t_data **data, int argc, char **argv)
{
	if (argc != 2 || !argv[1])
		return (1);
	*data = ft_calloc(1, sizeof(t_data));
	if (!*data)
		return (ERROR_MALLOC);
	(*data)->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	get_map(&(*data)->map, argv);
	return (0);
}

int	init_player(t_data *data)
{
	t_player	*player;
	mlx_image_t	*img;

	player = ft_calloc(1, sizeof(t_player));
	if (player == NULL)
		return (ERROR_MALLOC);
	player->img = mlx_new_image(data->mlx, 16, 16);
	if (player == NULL)
		return (ERROR_MALLOC);
	img = player->img;
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int));
	player->speed = WALK;
	data->player = player;
	return (0);
}

int	init_walls(t_data *data)
{
	mlx_image_t	*walls;

	walls = mlx_new_image(data->mlx, 64, 64);
	if (walls == NULL)
		return (ERROR_MALLOC);
	ft_memset(walls->pixels, 180, walls->width * walls->height * sizeof(int));
	data->walls = walls;
	return (0);
}

int	init(t_data **data, int argc, char **argv)
{
	if (init_data(data, argc, argv) != 0)
		return (1);
	if (init_player(*data) != 0)
		return (2);
	if (init_walls(*data) != 0)
		return (3);
	if (init_player(*data) != 0)
		return (4);
	return (0);
}
