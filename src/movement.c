/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:54:35 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/14 15:36:59 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_data *data, t_player *player, int step)
{
	mlx_instance_t	*inst;
	int	ts;

	inst = &player->img->instances[0];
	ts = data->ts;
	if (collision(data, inst->x, inst->y - step, data->map))
		inst->y = (((inst->y - step) / ts) + 1) * ts;
	else
		inst->y -= step;
}

void	move_down(t_data *data, t_player *player, int step)
{
	mlx_instance_t	*inst;
	int	ts;
	int	ps;

	inst = &player->img->instances[0];
	ts = data->ts;
	ps = data->ps;
	if (collision(data, inst->x, inst->y + step, data->map))
		inst->y = ((inst->y + step + ps) / ts) * ts - ps;
	else
		inst->y += step;
}

void	move_left(t_data *data, t_player *player, int step)
{
	mlx_instance_t	*inst;
	int	ts;

	inst = &player->img->instances[0];
	ts = data->ts;
	if (collision(data, inst->x - step, inst->y, data->map))
		inst->x = (((inst->x - step) / ts) + 1) * ts;
	else
		inst->x -= step;
}

void	move_right(t_data *data, t_player *player, int step)
{
	mlx_instance_t	*inst;
	int	ts;
	int	ps;

	inst = &player->img->instances[0];
	ts = data->ts;
	ps = data->ps;
	if (collision(data, inst->x + step, inst->y, data->map))
		inst->x = ((inst->x + step + ps) / ts) * ts - ps;
	else
		inst->x += step;
}

void	player_move(t_data *data)
{
	mlx_image_t	*player;
	int	x;
	int	y;

	player = data->player->img;
	x = player->instances[0].x;
	y = player->instances[0].y;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_up(data, data->player, data->player->speed);
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_down(data, data->player, data->player->speed);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left(data, data->player, data->player->speed);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right(data, data->player, data->player->speed);
}
