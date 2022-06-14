/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:54:35 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/14 13:28:21 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_up(t_data *data, t_player *player, mlx_instance_t *inst)
{
	int	ts;

	ts = data->ts;
	if (collision(data, inst->x, inst->y - player->speed, data->map))
		inst->y = (((inst->y - player->speed) / ts) + 1) * ts;
	else
		inst->y -= player->speed;
}

static void	move_down(t_data *data, t_player *player, mlx_instance_t *inst)
{
	int	ts;
	int	ps;

	ts = data->ts;
	ps = data->ps;
	if (collision(data, inst->x, inst->y + player->speed, data->map))
		inst->y = ((inst->y + player->speed + ps) / ts) * ts - ps;
	else
		inst->y += player->speed;
}

static void	move_left(t_data *data, t_player *player, mlx_instance_t *inst)
{
	int	ts;

	ts = data->ts;
	if (collision(data, inst->x - player->speed, inst->y, data->map))
		inst->x = (((inst->x - player->speed) / ts) + 1) * ts;
	else
		inst->x -= player->speed;
}

static void	move_right(t_data *data, t_player *player, mlx_instance_t *inst)
{
	int	ts;
	int	ps;

	ts = data->ts;
	ps = data->ps;
	if (collision(data, inst->x + player->speed, inst->y, data->map))
		inst->x = ((inst->x + player->speed + ps) / ts) * ts - ps;
	else
		inst->x += player->speed;
}

void	player_move(t_data *data)
{
	mlx_image_t	*player;
	int	x;
	int	y;

	player = data->player->img;
	x = player->instances[0].x;
	y = player->instances[0].y;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		move_up(data, data->player, &data->player->img->instances[0]);
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		move_down(data, data->player, &data->player->img->instances[0]);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		move_left(data, data->player, &data->player->img->instances[0]);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		move_right(data, data->player, &data->player->img->instances[0]);
}
