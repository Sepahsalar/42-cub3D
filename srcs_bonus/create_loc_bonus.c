/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_loc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:07:14 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/29 11:32:13 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	check_nb_player(t_all *all, int nb_player)
{
	if (nb_player != 1)
		terminate(all, "There must be one player", NULL, NULL);
}

static void	check_character_increase_player(char c, int *nb_player)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*nb_player)++;
}

void	check_max_node(t_all *all, t_coordinate *coordinate)
{
	coordinate->index++;
	if (coordinate->index >= MAX_NODE)
		terminate(all, "Too big map", NULL, NULL);
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
	coordinate.index = 0;
	nb_player = 0;
	while (*temp)
	{
		if (*temp != ' ' && *temp != '\n')
		{
			check_character_increase_player(*temp, &nb_player);
			check_max_node(all, &coordinate);
			new = create_loc_node(*temp, coordinate.x, coordinate.y);
			link_new_node(all, new, old);
			old = new;
		}
		update_coordinate(&coordinate, temp);
		temp++;
	}
	check_nb_player(all, nb_player);
}
