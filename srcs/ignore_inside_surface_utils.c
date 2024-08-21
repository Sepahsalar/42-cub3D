/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_inside_surface_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:24:54 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/21 10:40:49 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ignore_upper_wall(t_all *all, t_loc *loc)
{
	if (loc->c == '1')
	{
		loc->nx = -1;
		loc->ny = -1;
	}
	else
	{
		ft_putendl_fd("Not surrounded by walls", 2);
		terminate(all, 1);
	}
}

void	ignore_lower_wall(t_all *all, t_loc *loc)
{
	if (loc->c == '1')
	{
		loc->sx = -1;
		loc->sy = -1;
	}
	else
	{
		ft_putendl_fd("Not surrounded by walls", 2);
		terminate(all, 1);
	}
}

void	ignore_left_wall(t_all *all, t_loc *loc)
{
	if (loc->c == '1')
	{
		loc->wx = -1;
		loc->wy = -1;
	}
	else
	{
		ft_putendl_fd("Not surrounded by walls", 2);
		terminate(all, 1);
	}
}

void	ignore_right_wall(t_all *all, t_loc *loc)
{
	if (loc->c == '1')
	{
		loc->ex = -1;
		loc->ey = -1;
	}
	else
	{
		ft_putendl_fd("Not surrounded by walls", 2);
		terminate(all, 1);
	}
}
