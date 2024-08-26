/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:44:02 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/26 09:45:01 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	is_wall_there(t_all *all, int x, int y)
{
	t_loc	*temp;

	temp = all->map->start;
	while (temp)
	{
		if (temp->x == x && temp->y == y && temp->c == '1')
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	move_press(void *param, char c)
{
	t_all	*all;
	double	new_x;
	double	new_y;

	all = (t_all *)param;
	new_x = all->x;
	new_y = all->y;
	if (all->angle >= 225 && all->angle < 315)
		temp_movment225(&new_x, &new_y, c);
	else if (all->angle >= 135 && all->angle < 225)
		temp_movment135(&new_x, &new_y, c);
	else if (all->angle >= 45 && all->angle < 135)
		temp_movment45(&new_x, &new_y, c);
	else
		temp_movment315(&new_x, &new_y, c);
	conditional_move(all, new_x, new_y);
}

void	move_repeat(void *param, char c)
{
	t_all	*all;

	all = (t_all *)param;
	if (all->started_button == 0)
	{
		move_press(param, c);
		all->start_time = ft_timestamp_milis(all);
		all->current_time = all->start_time;
		all->started_button = 1;
	}
	all->current_time = ft_timestamp_milis(all);
	if (all->current_time - all->start_time >= RENDER_INTERVAL)
	{
		move_press(param, c);
		all->start_time = ft_timestamp_milis(all);
		all->current_time = all->start_time;
	}
}
