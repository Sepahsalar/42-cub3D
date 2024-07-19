/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:04:30 by nnourine          #+#    #+#             */
/*   Updated: 2024/03/05 13:13:32 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

int	ft_check_all_collectible_done(t_window_elements *window_elements)
{
	mlx_image_t	*collectible;
	int			count;
	int			index;

	collectible = (window_elements->elements)->collectible;
	count = collectible->count;
	index = 0;
	while (index < count)
	{
		if (collectible->instances[index].enabled)
			return (0);
		index++;
	}
	return (1);
}

void	ft_check_reach_to_exit(t_window_elements *window_elements,
	mlx_image_t *player,	mlx_image_t *exit)
{
	int			px;
	int			py;
	int			ex;
	int			ey;

	px = player->instances[0].x;
	py = player->instances[0].y;
	ex = exit->instances[0].x;
	ey = exit->instances[0].y;
	if (ex == px && ey == py)
		ft_exit_success(window_elements->window, window_elements->elements);
}

void	ft_check_exit(t_window_elements *window_elements)
{
	mlx_image_t	*player;
	mlx_image_t	*exit;

	player = (window_elements->elements)->player;
	exit = (window_elements->elements)->exit;
	if (!ft_check_all_collectible_done(window_elements))
		return ;
	ft_check_reach_to_exit(window_elements, player, exit);
}
