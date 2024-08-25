/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nima <nnourine@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:23:58 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/25 17:17:33 by nima             ###   ########.fr       */
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

void change_weapon(void *param)
{
	t_all	*all;
	
	all = (t_all *)param;
	if (all->active_weapon == 0)
	{
		all->knife->instances[0].enabled = true;
		all->gun->instances[0].enabled = false;
		all->active_weapon = 1;
	}
	else if (all->active_weapon == 1)
	{
		all->knife->instances[0].enabled = false;
		all->gun->instances[0].enabled = true;
		all->active_weapon = 0;
	}
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

void use_weapon(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	all->gun_used = 1;
	if (all->active_weapon == 0)
		all->gun->instances[0].y = END_GUN_Y;
	else if (all->active_weapon == 1)
	{
		all->knife->instances[0].x = 650;
		all->knife->instances[0].y = 760;
	}
}

void start_timer(t_all *all)
{
	if(all->animation_started == 0)
	{
		all->time1 = ft_timestamp_milis(all);
		all->animation_started = 1;			
	}
}

void end_animation(t_all *all)
{
	all->gun_used = 0;
	all->animation_started = 0;
}

void gun_animation(t_all *all)
{
	start_timer(all);
	all->time2 = ft_timestamp_milis(all);
	if (all->time2 > all->time1 + 500)
	{
		all->gun->instances[0].y = START_GUN_Y;
		end_animation(all);
	}
	if (all->time2 > all->time1 + 400)
		all->blast->instances[0].enabled = false;
	else if (all->time2 > all->time1 + 250)
	{
		all->gun->instances[0].x = START_GUN_X;
		all->blast->instances[0].enabled = true;
	}
	else if (all->time2 > all->time1 + 200)
		all->gun->instances[0].x = START_GUN_X + 50;
}

void knife_animation(t_all *all)
{
	start_timer(all);
	all->time2 = ft_timestamp_milis(all);
	if (all->time2 > all->time1 + 200)
	{
		all->knife->instances[0].x = 700;
		all->knife->instances[0].y = 810;
		end_animation(all);
	}
}

void animation(void *param)
{
	t_all	*all;

	all = (t_all *) param;
	if (all->gun_used)
	{
		if (all->active_weapon == 1)
			knife_animation(all);
		else if (all->active_weapon == 0)
			gun_animation(all);
	}
}

void click(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		use_weapon(param);
	else if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		change_weapon(param);
}

void	mouse(double xpos, double ypos, void *param)
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

void	scroll(double xpos, double ypos, void *param)
{
	(void)xpos;
	if (ypos > 0)
		move_repeat(param, 'W');
	else if (ypos < 0)
		move_repeat(param, 'S');
}

void key_press(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_W)
		move_press(param, 'W');
	else if (keydata.key == MLX_KEY_S)
		move_press(param, 'S');
	else if (keydata.key == MLX_KEY_A)
		move_press(param, 'A');
	else if (keydata.key == MLX_KEY_D)
		move_press(param, 'D');
	else if (keydata.key == MLX_KEY_SPACE)
		use_weapon(param);
	else if (keydata.key == MLX_KEY_LEFT)
		turn_press(param, 'L');
	else if (keydata.key == MLX_KEY_RIGHT)
		turn_press(param, 'R');
	else if (keydata.key == MLX_KEY_LEFT_SHIFT
		|| keydata.key == MLX_KEY_RIGHT_SHIFT)
		change_weapon(param);
	else if (keydata.key == MLX_KEY_ESCAPE)
		terminate(param, 0);
}

void key_repeat(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_W)
		move_repeat(param, 'W');
	else if (keydata.key == MLX_KEY_S)
		move_repeat(param, 'S');
	else if (keydata.key == MLX_KEY_A)
		move_repeat(param, 'A');
	else if (keydata.key == MLX_KEY_D)
		move_repeat(param, 'D');
	else if (keydata.key == MLX_KEY_LEFT)
		turn_repeat(param, 'L');
	else if (keydata.key == MLX_KEY_RIGHT)
		turn_repeat(param, 'R');
}

void key_release(mlx_key_data_t keydata, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (keydata.key == MLX_KEY_W
		|| keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_A
		|| keydata.key == MLX_KEY_D
		|| keydata.key == MLX_KEY_LEFT
		|| keydata.key == MLX_KEY_RIGHT)
		all->started_button = 0;
}

void	keyboard(mlx_key_data_t keydata, void *param)
{
	if (keydata.action == MLX_PRESS)
		key_press(keydata, param);
	else if (keydata.action == MLX_REPEAT)
		key_repeat(keydata, param);
	else if (keydata.action == MLX_RELEASE)
		key_release(keydata, param);
}
