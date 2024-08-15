/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_loc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:07:14 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/15 12:22:20 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	check_nb_player(t_all *all, int nb_player)
{
	if (nb_player != 1)
	{
		ft_putendl_fd("There must be one player", 2);
		terminate(all, 1);
	}
}

static void	check_character_increase_player(char c, int *nb_player)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*nb_player)++;
}

void	create_loc(t_all *all)
{
	t_loc			*new;
	t_loc			*old;
	char			*temp;
	t_coordinate	coordinate;
	int				nb_player;

	temp = all->strmap;
	coordinate.x = 0;
	coordinate.y = 0;
	nb_player = 0;
	while (*temp)
	{
		if (*temp != ' ' && *temp != '\n')
		{
			check_character_increase_player(*temp, &nb_player);
			new = create_loc_node(*temp, coordinate.x, coordinate.y);
			link_new_node(all, new, old);
			old = new;
		}
		update_coordinate(&coordinate, temp);
		temp++;
	}
	check_nb_player(all, nb_player);
}
