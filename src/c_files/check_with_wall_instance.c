/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_with_wall_instance.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:08:55 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/19 16:06:05 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_check_with_wall_instance_up(mlx_image_t *player,
	mlx_image_t *wall, int index)
{
	int			px;
	int			py;
	int			wx;
	int			wy;

	px = player->instances[0].x;
	py = player->instances[0].y;
	wx = wall->instances[index].x;
	wy = wall->instances[index].y;
	if ((wx == px) && (wy == (py - (int)((*player).height))))
		return (0);
	return (index + 1);
}

int	ft_check_with_wall_instance_down(mlx_image_t *player,
	mlx_image_t *wall, int index)
{
	int			px;
	int			py;
	int			wx;
	int			wy;

	px = player->instances[0].x;
	py = player->instances[0].y;
	wx = wall->instances[index].x;
	wy = wall->instances[index].y;
	if ((wx == px) && (wy == (py + (int)((*player).height))))
		return (0);
	return (index + 1);
}

int	ft_check_with_wall_instance_left(mlx_image_t *player,
	mlx_image_t *wall, int index)
{
	int			px;
	int			py;
	int			wx;
	int			wy;

	px = player->instances[0].x;
	py = player->instances[0].y;
	wx = wall->instances[index].x;
	wy = wall->instances[index].y;
	if ((wx == (px - (int)((*player).width))) && (wy == py))
		return (0);
	return (index + 1);
}

int	ft_check_with_wall_instance_right(mlx_image_t *player,
	mlx_image_t *wall, int index)
{
	int			px;
	int			py;
	int			wx;
	int			wy;

	px = player->instances[0].x;
	py = player->instances[0].y;
	wx = wall->instances[index].x;
	wy = wall->instances[index].y;
	if ((wx == (px + (int)((*player).width))) && (wy == py))
		return (0);
	return (index + 1);
}

int	ft_check_with_wall_instance(mlx_image_t *player,
	mlx_image_t *wall, int index, char move)
{
	if (move == 'U')
		return (ft_check_with_wall_instance_up(player, wall, index));
	else if (move == 'D')
		return (ft_check_with_wall_instance_down(player, wall, index));
	else if (move == 'L')
		return (ft_check_with_wall_instance_left(player, wall, index));
	else
		return (ft_check_with_wall_instance_right(player, wall, index));
}
