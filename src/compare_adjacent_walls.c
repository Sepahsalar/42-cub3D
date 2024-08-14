/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_adjacent_walls.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:56:09 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/14 19:00:28 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	south_to_north(t_loc *temp1, t_loc *temp2)
{
	temp1->sx = -1;
	temp1->sy = -1;
	temp2->nx = -1;
	temp2->ny = -1;
}

static void	north_to_south(t_loc *temp1, t_loc *temp2)
{
	temp1->nx = -1;
	temp1->ny = -1;
	temp2->sx = -1;
	temp2->sy = -1;
}

static void	east_to_west(t_loc *temp1, t_loc *temp2)
{
	temp1->ex = -1;
	temp1->ey = -1;
	temp2->wx = -1;
	temp2->wy = -1;
}

static void	west_to_east(t_loc *temp1, t_loc *temp2)
{
	temp1->wx = -1;
	temp1->wy = -1;
	temp2->ex = -1;
	temp2->ey = -1;
}

void	compare_adjacent_walls(t_loc *temp1, t_loc *temp2)
{
	if (temp2->c == '1')
	{
		if (temp1->sx == temp2->nx && temp1->sy == temp2->ny)
			south_to_north(temp1, temp2);
		else if (temp1->nx == temp2->sx && temp1->ny == temp2->sy)
			north_to_south(temp1, temp2);
		else if (temp1->ex == temp2->wx && temp1->ey == temp2->wy)
			east_to_west(temp1, temp2);
		else if (temp1->wx == temp2->ex && temp1->wy == temp2->ey)
			west_to_east(temp1, temp2);
	}
}
