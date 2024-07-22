/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reach_to_collectible.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:04:14 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/19 16:06:05 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_modify_collectible_list(t_collectible_position *collectible,
	int cx, int cy)
{
	t_collectible_position			*node;

	node = collectible;
	while (node)
	{
		if ((*node).x == cx && (*node).y == cy)
		{
			(*node).enabled = 0;
			break ;
		}
		node = node->next;
	}
}

void	ft_check_with_collectible_instance(mlx_image_t *player,
	mlx_image_t *collectible, int index, t_elements	*elements)
{
	int								px;
	int								py;
	int								cx;
	int								cy;
	t_collectible_position			*collectible_list;

	px = player->instances[0].x;
	py = player->instances[0].y;
	cx = collectible->instances[index].x;
	cy = collectible->instances[index].y;
	collectible_list = (elements->player_collectible)->collectible;
	if (cx == px && cy == py)
	{
		ft_modify_collectible_list(collectible_list,
			(cx / (collectible->width)), (cy / (collectible->height)));
		collectible->instances[index].enabled = 0;
	}
}

void	ft_check_reach_to_collectible(t_window_elements *window_elements)
{
	mlx_image_t	*player;
	mlx_image_t	*collectible;
	t_elements	*elements;
	int			count;
	int			index;

	player = (window_elements->elements)->player;
	collectible = (window_elements->elements)->collectible;
	count = collectible->count;
	elements = window_elements->elements;
	index = 0;
	while (index < count)
	{
		ft_check_with_collectible_instance(player,
			collectible, index, elements);
		index++;
	}
}
