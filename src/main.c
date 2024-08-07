/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:43:59 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/07 14:19:38 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// add deleting mlx42 in makefile

double ft_tan(double a)
{
	double angle;

	angle = M_PI * a / 180;
	return (tan(angle));
}

double ft_sin(double a)
{
	double angle;

	angle = M_PI * a / 180;
	return (sin(angle));
}

double ft_cos(double a)
{
	double angle;

	angle = M_PI * a / 180;
	return (cos(angle));
}

double find_y(double angle, double x_player, double y_player, int x_target)
{
	double	y_target;
	
	y_target = ((x_target - x_player) * ft_tan(angle)) + y_player;
	return (y_target);
	
}

double find_x(double angle, double x_player, int y_player, int y_target)
{
	double	x_target;

	x_target = ((y_target - y_player) / ft_tan(angle)) + x_player;
	return (x_target);
	
}

double distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

double min_x(double x_player, double angle)
{
	while (angle < 0)
		angle = angle + FULL_CIRCLE_DEGREES;
	if (angle >= 0 && angle <= FULL_CIRCLE_DEGREES / 4)
		return(x_player);
	else if (angle > FULL_CIRCLE_DEGREES / 4
		&& angle <= FULL_CIRCLE_DEGREES * 3 / 4)
		return (0);
	else
		return (x_player);
}

double max_x(double x_player, int x_game_size, double angle)
{
	while (angle < 0)
		angle = angle + FULL_CIRCLE_DEGREES;
	if (angle >= 0 && angle <= FULL_CIRCLE_DEGREES / 4)
		return(x_game_size);
	else if (angle > FULL_CIRCLE_DEGREES / 4
		&& angle <= FULL_CIRCLE_DEGREES * 3 / 4)
		return (x_player);
	else
		return (x_game_size);
}

double min_y(double y_player, double angle)
{
	while (angle < 0)
		angle = angle + FULL_CIRCLE_DEGREES;
	if (angle >= 0 && angle <= FULL_CIRCLE_DEGREES / 2)
		return(y_player);
	else
		return (0);
}

double max_y(double y_player, int y_game_size, double angle)
{
	while (angle < 0)
		angle = angle + FULL_CIRCLE_DEGREES;
	if (angle >= 0 && angle <= FULL_CIRCLE_DEGREES / 2)
		return(y_game_size);
	else
		return (y_player);
}

double start_loc_player(t_all *all, char c)
{
	t_loc *loc;

	loc = all->map->start;
	while (loc)
	{
		if (loc->c == 'N' || loc->c == 'S' || loc->c == 'W' || loc->c == 'E')
		{
			if (c == 'x')
				return (loc->x_mid);
			else
				return (loc->y_mid);
		}
		loc = loc->next;
	}
	return (-1);
}

double start_angle_player(t_all *all)
{
	t_loc *loc;

	loc = all->map->start;
	while (loc)
	{
		if (loc->c == 'N' || loc->c == 'S' || loc->c == 'W' || loc->c == 'E')
		{
			if (loc->c == 'N')
				return ((double)270);
			else if (loc->c == 'S')
				return ((double)90);
			else if (loc->c == 'W')
				return ((double)0);
			else
				return ((double)180);
		}
		loc = loc->next;
	}
	return (-1);
}

int	game_size(t_all *all, char c)
{
	t_loc *loc;
	int i;

	loc = all->map->start;
	i = 0;
	while (loc)
	{
		if (c == 'x')
		{
			if (i < loc->x)
				i = loc->x;
		}
		else
		{
			if (i < loc->y)
				i = loc->y;
		}
		loc = loc->next;
	}
	return (i + 1);
}

double max_distance(t_all *all)
{
	double x;
	double	y;

	x = game_size(all, 'x');
	y = game_size(all, 'y');
	return (sqrt(pow(x, 2) + pow(y, 2)));
}

char	wall_helper(char c1, char c2, char c3)
{	
	if (c1 == 'x')
		return (c2);
	else
		return (c3);
}

char	wall_selection(double angle, char c)
{
	while (angle < 0)
		angle = angle + FULL_CIRCLE_DEGREES;
	while (angle > 360)
		angle = angle - FULL_CIRCLE_DEGREES;
	if (angle >= 0 && angle <= FULL_CIRCLE_DEGREES / 4)
		return (wall_helper(c, 'W', 'N'));
	else if (angle > FULL_CIRCLE_DEGREES / 4
		&& angle <= FULL_CIRCLE_DEGREES / 2)
		return (wall_helper(c, 'E', 'N'));
	else if (angle > FULL_CIRCLE_DEGREES / 2
		&& angle <= FULL_CIRCLE_DEGREES * 3 / 4)
		return (wall_helper(c, 'E', 'S'));
	else
		return (wall_helper(c, 'W', 'S'));
}

double height(double distance, char c)
{
	double half_full_height;
	double target_height;
	
	half_full_height = ft_tan(VAOV / 2) * distance;
	if (c == 'F')
		target_height = half_full_height - PERSON;
	else
		target_height = half_full_height - WALL + PERSON;
	if (target_height <= 0)
		return (0);
	else
		return ((WINDOW_HEIGHT * target_height / (2 * half_full_height)));
}

double find_right_distance(t_all *all)
{
	t_loc	*temp_loc;
	double	temp_distance;
	double	x_player;
	double	y_player;
	double 	max_d;
	double 	x_min;
	double 	x_max;
	int 	x_size_game;
	
	x_player = start_loc_player(all, 'x');
	y_player = start_loc_player(all, 'y');
	max_d = max_distance(all);
	x_size_game = game_size(all, 'x');
	x_min = min_x(x_player, 360);
	x_max = max_x(x_player, x_size_game, 360);
	temp_distance = max_d;
	temp_loc = all->map->start;
	while (temp_loc)
	{
		if (temp_loc->y_mid == y_player && temp_loc->x_mid <= x_max && temp_loc->x_mid >= x_min && temp_loc->c == '1')
			if (fabs(temp_loc->x_mid - x_player) < temp_distance)
				temp_distance = fabs(temp_loc->x_mid - x_player);
		temp_loc = temp_loc->next;
	}
	return (temp_distance);
}

void	size_grid(t_all *all)
{
	t_loc		*temp_loc;
	double		temp_x;
	double		temp_y;
	double		x_player;
	double		y_player;
	double		angle_player;
	double		temp_angle;
	double		ray_angle;
	int 		x_size_game;
	int 		y_size_game;
	double 		x_min;
	double 		x_max;
	double 		y_min;
	double 		y_max;
	int 		i;
	double 		max_d;
	char 		type_intersection;
	double 		temp_distance;
	t_render	data_rander;
	double 		distance_left;
	double 		distance_right;
	int			counter;

	x_player = all->x;
	y_player = all->y;
	angle_player = all->angle;
	x_size_game = game_size(all, 'x');
	y_size_game = game_size(all, 'y');
	max_d = max_distance(all);
	temp_angle = 0;
	counter = 0;
	while (counter <= NLOOP)
	{
		ray_angle = angle_player - (HAOV / 2) + temp_angle;
		x_min = min_x(x_player, ray_angle);
		x_max = max_x(x_player, x_size_game, ray_angle);
		y_min = min_y(y_player, ray_angle);
		y_max = max_y(y_player, y_size_game, ray_angle);
		temp_distance = max_d;
		i = x_min;
		if (ceil(ray_angle) == floor(ray_angle) && (int)ray_angle % 180 == 90)
		{
			temp_loc = all->map->start;
			while (temp_loc)
			{
				if (temp_loc->x_mid == x_player && temp_loc->y_mid <= y_max && temp_loc->y_mid >= y_min && temp_loc->c == '1')
				{
					if (fabs(temp_loc->y_mid - y_player) < temp_distance)
					{
						temp_distance = fabs(temp_loc->y_mid - y_player);
						type_intersection = 'y';
					}
				}
				temp_loc = temp_loc->next;
			}
		}
		else if (ceil(ray_angle) == floor(ray_angle) && (int)ray_angle % 180 == 0)
		{
			temp_loc = all->map->start;
			while (temp_loc)
			{
				if (temp_loc->y_mid == y_player && temp_loc->x_mid <= x_max && temp_loc->x_mid >= x_min && temp_loc->c == '1')
				{
					if (fabs(temp_loc->x_mid - x_player) < temp_distance)
					{
						temp_distance = fabs(temp_loc->x_mid - x_player);
						type_intersection = 'x';
					}
				}
				temp_loc = temp_loc->next;
			}
		}
		else
		{
			while (i <= x_max)
			{
				temp_loc = all->map->start;
				temp_y = find_y(ray_angle, x_player, y_player, i);
				while (temp_loc)
				{
					if (temp_loc->x0 <= i && i <= temp_loc->x1 && temp_loc->y0 <= temp_y &&  temp_y <= temp_loc->y1 && temp_loc->c == '1')
					{
						if (distance((double)i, temp_y, x_player, y_player) < temp_distance)
						{
							temp_distance = distance((double)i, temp_y, x_player, y_player);
							type_intersection = 'x';
						}
					}
					temp_loc = temp_loc->next;
				}
				i++;
			}
			i = y_min;
			while(i <= y_max)
			{
				temp_loc = all->map->start;
				temp_x = find_x(ray_angle, x_player, y_player, i);
				while (temp_loc)
				{
					if (temp_loc->y0 <= i && i <= temp_loc->y1 && temp_loc->x0 <= temp_x && temp_x <= temp_loc->x1 && temp_loc->c == '1')
					{
						if (distance(temp_x, (double)i, x_player, y_player) < temp_distance)
						{
							temp_distance = distance(temp_x, (double)i, x_player, y_player);
							type_intersection = 'y';
						}
					}
					temp_loc = temp_loc->next;
				}
				i++;
			}
		}
		if (temp_angle == 0)
			distance_left = temp_distance;
		distance_right = find_right_distance(all);
		if (temp_angle >= 0 && temp_angle <= 90)
			temp_distance = temp_distance * fabs(ft_sin(temp_angle)) + distance_left;
		else
			temp_distance = temp_distance * fabs(ft_sin(temp_angle)) + distance_right;
		data_rander.wall_texture = wall_selection(ray_angle, type_intersection);
		data_rander.floor_height = height(temp_distance, 'F');
		data_rander.ceil_height = height(temp_distance, 'C');
		
		data_rander.wall_height = WINDOW_HEIGHT - data_rander.ceil_height - data_rander.floor_height;
		data_rander.x = (int)(temp_angle / WIDTH_INTERVAL);
		create_strip(all, data_rander);
		counter++;
		temp_angle+= WIDTH_INTERVAL;
	}
}

void render(t_all *all)
{
	size_grid(all);
	fill_index_strip(all);
	fill_length_strip(all);
	strip_to_image(all);
}

int main(int argc, char **argv)
{
	t_all *all;

	(void)argc;
	all = malloc(sizeof(t_all));
	if (!all)
		terminate(all, 1);
	all->argv = argv[1];
	all->fd = -1;
	all->map = map_parser(all);
	all->strip = NULL;
	all->floor_color = color_maker(all, 'f');
	all->ceil_color = color_maker(all, 'c');
	all->x = start_loc_player(all, 'x');
	all->y = start_loc_player(all, 'y');
	all->angle = start_angle_player(all);	
	all->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT,	argv[0], false);
	if (!all->window)
		terminate(all, 1);
	render(all);
	mlx_key_hook(all->window, &press_key, all);	
	mlx_loop(all->window);
	terminate(all, 0);
}
