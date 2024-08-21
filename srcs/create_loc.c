/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_loc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:07:14 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/21 16:35:46 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	coordinate.index = 0;
	nb_player = 0;
	// printf("create_loc\n");
	while (*temp)
	{
		if (*temp != ' ' && *temp != '\n')
		{
			check_character_increase_player(*temp, &nb_player);
			coordinate.index++;
			if (coordinate.index >= MAX_NODE)
			{
				ft_putendl_fd("Too big map", 2);
				terminate(all, 1);
			}
			new = create_loc_node(*temp, coordinate.x, coordinate.y);
			link_new_node(all, new, old);
			old = new;
		}
		update_coordinate(&coordinate, temp);
		temp++;
	}
	check_nb_player(all, nb_player);
}
