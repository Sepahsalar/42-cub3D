/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:23:58 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/23 11:30:43 by nnourine         ###   ########.fr       */
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

static void	turn_press(void *param, char c)
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

static void	turn_repeat(void *param, char c)
{
	t_all	*all;

	all = (t_all *)param;
	if (all->started_button == 0)
	{
		turn_press(param, c);
		all->start_time = ft_timestamp_milis(all);
		all->current_time  = all->start_time;
		all->started_button = 1;
	}
	all->current_time =ft_timestamp_milis(all);
	if (all->current_time - all->start_time >= RENDER_INTERVAL)
	{
		turn_press(param, c);
		all->start_time = ft_timestamp_milis(all);
		all->current_time  = all->start_time;
	}
}

static void	move_press(void *param, char c)
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

static void	move_repeat(void *param, char c)
{
	t_all	*all;

	all = (t_all *)param;
	if (all->started_button == 0)
	{
		move_press(param, c);
		all->start_time = ft_timestamp_milis(all);
		all->current_time  = all->start_time;
		all->started_button = 1;
	}
	all->current_time =ft_timestamp_milis(all);
	if (all->current_time - all->start_time >= RENDER_INTERVAL)
	{
		move_press(param, c);
		all->start_time = ft_timestamp_milis(all);
		all->current_time  = all->start_time;
	}
}

void shoot(void *param, char type)
{
	t_all	*all;

	all = (t_all *)param;
	if (type == '0')
	{
		all->gun->instances[0].y = END_GUN_Y;
		all->blast->instances[0].enabled = true;
		all->started_button = 1;
	}
	else if (type == '1')
	{
		all->gun->instances[0].y = START_GUN_Y;
		all->blast->instances[0].enabled = false;
		all->started_button = 0;
	}
	// else if (type == '2')
	// {
	// 	all->blast->instances[0].enabled =false;
	// 	all->gun->instances[0].y = START_GUN_Y;
	// }
}

void	mouse(double xpos, double ypos, void* param)
{
	t_all	*all;

	all = (t_all *)param;
	(void)ypos;
	if (xpos > all->x_mouse)
		turn_repeat(param, 'R');
	else if (xpos < all->x_mouse)
		turn_repeat(param, 'L');
	all->x_mouse = xpos;
	
	
}

void	press_key(mlx_key_data_t keydata, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_press(param, 'W');
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_press(param, 'S');
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_press(param, 'A');
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_press(param, 'D');
	
	else if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		shoot(param, '0');
	else if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_RELEASE)
		shoot(param, '1');
	else if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_REPEAT)
		shoot(param, '1');
	
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT)
		move_repeat(param, 'W');
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_REPEAT)
		move_repeat(param, 'S');
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_REPEAT)
		move_repeat(param, 'A');
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_REPEAT)
		move_repeat(param, 'D');
	
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		all->started_button = 0;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		all->started_button = 0;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		all->started_button = 0;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		all->started_button = 0;
	
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		turn_press(param, 'L');
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		turn_press(param, 'R');
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT)
		turn_repeat(param, 'L');
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT)
		turn_repeat(param, 'R');
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		all->started_button = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		all->started_button = 0;
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		terminate(param, 0);
}
