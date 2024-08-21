/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:23:58 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/21 10:40:49 by nnourine         ###   ########.fr       */
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

double	under_full_circle(double angle)
{
	if (angle >= FULL_CIRCLE_DEGREES)
		return (angle -= FULL_CIRCLE_DEGREES);
	if (angle < 0)
		return (angle += FULL_CIRCLE_DEGREES);
	return (angle);
}

static void	turn(void *param, char c)
{
	t_all	*all;

	all = (t_all *)param;
	clean_strips(all);
	mlx_delete_image(all->window, all->image);
	if (c == 'R')
		all->angle += TURN_INTERVAL;
	else
		all->angle -= TURN_INTERVAL;
	all->angle = under_full_circle(all->angle);
	fill_strips(all);
}

static void	move(void *param, char c)
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

void	press_key(mlx_key_data_t keydata, void *param)
{
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& keydata.action == MLX_PRESS)
		move(param, 'W');
	else if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			&& keydata.action == MLX_PRESS)
		move(param, 'S');
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move(param, 'A');
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move(param, 'D');
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		turn(param, 'L');
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		turn(param, 'R');
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		terminate(param, 0);
}
