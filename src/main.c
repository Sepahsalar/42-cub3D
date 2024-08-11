/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nima <nnourine@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:43:59 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/11 10:36:42 by nima             ###   ########.fr       */
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

// double find_y(double angle, double x_player, double y_player, int x_target)
// {
// 	double	y_target;
	
// 	y_target = ((x_target - x_player) * ft_tan(angle)) + y_player;
// 	return (y_target);
	
// }

// double find_x(double angle, double x_player, int y_player, int y_target)
// {
// 	double	x_target;

// 	x_target = ((y_target - y_player) / ft_tan(angle)) + x_player;
// 	return (x_target);
	
// }

double find_y(double angle, double x_player, double y_player, double x_target)
{
	double	y_target;
	
	y_target = ((x_target - x_player) * ft_tan(angle)) + y_player;
	return (y_target);
	
}

double find_x(double angle, double x_player, double y_player, double y_target)
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
	// while (angle < 0)
	// 	angle = angle + FULL_CIRCLE_DEGREES;
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
	// while (angle < 0)
	// 	angle = angle + FULL_CIRCLE_DEGREES;
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
	// while (angle < 0)
	// 	angle = angle + FULL_CIRCLE_DEGREES;
	if (angle >= 0 && angle < FULL_CIRCLE_DEGREES / 2)
		return(y_player);
	else
		return (0);
}

double max_y(double y_player, int y_game_size, double angle)
{
	// while (angle < 0)
	// 	angle = angle + FULL_CIRCLE_DEGREES;
	if (angle >= 0 && angle < FULL_CIRCLE_DEGREES / 2)
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
	while (angle > FULL_CIRCLE_DEGREES)
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

// double find_right_distance(t_all *all)
// {
// 	t_loc	*temp_loc;
// 	double	temp_distance;
// 	double	x_player;
// 	double	y_player;
// 	double 	max_d;
// 	double 	x_min;
// 	double 	x_max;
// 	int 	x_size_game;
	
// 	x_player = start_loc_player(all, 'x');
// 	y_player = start_loc_player(all, 'y');
// 	max_d = max_distance(all);
// 	x_size_game = game_size(all, 'x');
// 	x_min = min_x(x_player, 360);
// 	x_max = max_x(x_player, x_size_game, 360);
// 	temp_distance = max_d;
// 	temp_loc = all->map->start;
// 	while (temp_loc)
// 	{
// 		if (temp_loc->y_mid == y_player && temp_loc->x_mid <= x_max && temp_loc->x_mid >= x_min && temp_loc->c == '1')
// 			if (fabs(temp_loc->x_mid - x_player) < temp_distance)
// 				temp_distance = fabs(temp_loc->x_mid - x_player);
// 		temp_loc = temp_loc->next;
// 	}
// 	return (temp_distance);
// }

int same(double d1, int d2)
{
	if (fabs(d1 - (double)d2) < EPSILON)
		return (1);
	return (0);
}

int same_double(double d1, double d2)
{
	if (fabs(d1 - d2) < EPSILON)
		return (1);
	return (0);
}

// void	size_grid(t_all *all)
// {
// 	t_loc		*temp_loc;
// 	double		temp_x;
// 	double		temp_y;
// 	double		x_player;
// 	double		y_player;
// 	double		angle_player;
// 	double		temp_angle;
// 	double		ray_angle;
// 	int 		x_size_game;
// 	int 		y_size_game;
// 	double 		x_min;
// 	double 		x_max;
// 	double 		y_min;
// 	double 		y_max;
// 	int 		i;
// 	double 		max_d;
// 	char 		type_intersection;
// 	double 		winner_distance;
// 	t_render	data_rander;
// 	double 		distance_left;
// 	double 		distance_right;
// 	int			counter;
// 	double		temp_dis;
// 	double		intersection_distance;

// 	x_player = all->x;
// 	y_player = all->y;
// 	angle_player = all->angle;
// 	x_size_game = all->map_width;
// 	y_size_game = all->map_height;
// 	max_d = all->max_distance;
// 	temp_angle = 0;
// 	counter = 0;
// 	while (counter <= NLOOP)
// 	{
// 		ray_angle = under_full_circle(angle_player - (HAOV / 2) + temp_angle);
// 		x_min = min_x(x_player, ray_angle);
// 		x_max = max_x(x_player, x_size_game, ray_angle);
// 		y_min = min_y(y_player, ray_angle);
// 		y_max = max_y(y_player, y_size_game, ray_angle);
// 		winner_distance = max_d;
// 		i = floor(x_min);
// 		if (same(ray_angle, 90) || same(ray_angle, 270))
// 		{
// 			temp_loc = all->map->start;
// 			while (temp_loc)
// 			{
// 				if (temp_loc->x_mid == x_player && temp_loc->y_mid <= y_max && temp_loc->y_mid >= y_min && temp_loc->c == '1')
// 				{
// 					temp_dis = fabs(temp_loc->y_mid - y_player);
// 					if (temp_dis < winner_distance)
// 					{
// 						winner_distance = temp_dis;
// 						intersection_distance = winner_distance - 0.5; //
// 						type_intersection = 'y';
// 					}
// 				}
// 				temp_loc = temp_loc->next;
// 			}
// 		}
// 		else if (same(ray_angle, 0) || same(ray_angle, 180))
// 		{
// 			temp_loc = all->map->start;
// 			while (temp_loc)
// 			{
// 				if (temp_loc->y_mid == y_player && temp_loc->x_mid <= x_max && temp_loc->x_mid >= x_min && temp_loc->c == '1')
// 				{
// 					temp_dis = fabs(temp_loc->x_mid - x_player);
// 					if (temp_dis < winner_distance)
// 					{
// 						winner_distance = temp_dis;
// 						intersection_distance = winner_distance - 0.5; //
// 						type_intersection = 'x';
// 					}
// 				}
// 				temp_loc = temp_loc->next;
// 			}
// 		}
// 		else
// 		{
// 			while (i <= ceil(x_max))
// 			{
// 				temp_loc = all->map->start;
// 				temp_y = find_y(ray_angle, x_player, y_player, i);
// 				while (temp_loc)
// 				{
// 					if (temp_loc->x0 <= i && i <= temp_loc->x1 && temp_loc->y0 <= temp_y &&  temp_y <= temp_loc->y1 && temp_loc->c == '1')
// 					{
// 						// temp_dis = distance((double)i, temp_y, x_player, y_player);
// 						temp_dis = distance((double)i, temp_loc->y_mid, x_player, y_player);
// 						if (temp_dis < winner_distance)
// 						{
// 							winner_distance = temp_dis;
// 							intersection_distance = distance((double)i, temp_y, x_player, y_player);
// 							type_intersection = 'x';
// 						}
// 					}
// 					temp_loc = temp_loc->next;
// 				}
// 				i++;
// 			}
// 			i = floor(y_min);
// 			while(i <= ceil(y_max))
// 			{
// 				temp_loc = all->map->start;
// 				temp_x = find_x(ray_angle, x_player, y_player, i);
// 				while (temp_loc)
// 				{
// 					if (temp_loc->y0 <= i && i <= temp_loc->y1 && temp_loc->x0 <= temp_x && temp_x <= temp_loc->x1 && temp_loc->c == '1')
// 					{
// 						// temp_dis = distance(temp_x, (double)i, x_player, y_player);
// 						temp_dis = distance(temp_loc->x_mid, (double)i, x_player, y_player);
// 						if (temp_dis < winner_distance)
// 						{
// 							winner_distance = temp_dis;
// 							intersection_distance = distance(temp_x, (double)i, x_player, y_player);
// 							type_intersection = 'y';
// 						}
// 					}
// 					temp_loc = temp_loc->next;
// 				}
// 				i++;
// 			}
// 		}
// 		if (intersection_distance < 0.5)
// 			intersection_distance = 0.5;
// 		if (same(temp_angle, 0))
// 			distance_left = intersection_distance;
// 		distance_right = find_right_distance(all);
// 		if (temp_angle >= 0 && temp_angle <= 90)
// 			intersection_distance = intersection_distance * fabs(ft_sin(temp_angle)) + distance_left;
// 		else
// 			intersection_distance = intersection_distance * fabs(ft_sin(temp_angle)) + distance_right;
// 		data_rander.wall_texture = wall_selection(ray_angle, type_intersection);
// 		data_rander.floor_height = height(intersection_distance, 'F');
// 		data_rander.ceil_height = height(intersection_distance, 'C');
// 		data_rander.wall_height = WINDOW_HEIGHT - data_rander.ceil_height - data_rander.floor_height;
// 		data_rander.x = (int)(temp_angle / WIDTH_INTERVAL);
// 		create_strip(all, data_rander);
// 		counter++;
// 		temp_angle+= WIDTH_INTERVAL;
// 	}
// }

double find_right_distance(t_all *all)
{
	// t_loc		*temp_loc;
	// double		temp_x;
	// double		temp_y;
	double		x_player;
	double		y_player;
	double		angle_player;
	double		temp_angle;
	double		ray_angle;
	int 		x_size_game;
	int 		y_size_game;
	// int			x_min;
	// int			x_max;
	// int			y_min;
	// int			y_max;
	// double		temp_x_min;
	// double		temp_y_min;
	// double		temp_x_max;
	// double		temp_y_max;
	// int 		i;
	// double 		max_d;
	// char 		type_intersection;
	// double 		winner_distance;
	// double		temp_dis;
	double		intersection_distance;
	t_range		range;
	t_possible *temp_pos;
	t_possible	*winner;
	char		winner_material;

	x_player = all->x;
	y_player = all->y;
	angle_player = all->angle;
	x_size_game = all->map_width;
	y_size_game = all->map_height;
	// max_d = all->max_distance;
	temp_angle = 180;
	ray_angle = under_full_circle(angle_player - (HAOV / 2) + temp_angle);
	intersection_distance = 0;
	// temp_x_min = min_x(x_player, ray_angle);
	// temp_x_max = max_x(x_player, x_size_game, ray_angle);
	// temp_y_min = min_y(y_player, ray_angle);
	// temp_y_max = max_y(y_player, y_size_game, ray_angle);
	// printf("temp_min_x: %f, temp_y_min: %f, temp_x_max:%f, temp_y_max:%f\n", temp_x_min, temp_y_min, temp_x_max, temp_y_max);
	// // winner_distance = max_d;
	// if (same(temp_x_min, 0))
	// {
	// 	range.x_min = 0;
	// 	range.x_max = ceil(x_player);
	// }
	// else
	// {
	// 	range.x_min = floor(temp_x_min);
	// 	range.x_max = all->map_width - 1;
	// }
	// if (same(temp_y_min , 0))
	// {
	// 	range.y_min = 0;
	// 	range.y_max = ceil(y_player);
	// }
	// else
	// {
	// 	range.y_min = floor(range.x_min);
	// 	range.y_max = all->map_height - 1;
	// }
	// printf("min_x: %d, y_min: %d, x_max:%d, y_max:%d\n", range.x_min, range.y_min, range.x_max, range.y_max);
	range.x_min = min_x(x_player, ray_angle);
	range.x_max = max_x(x_player, x_size_game, ray_angle);
	range.y_min = min_y(y_player, ray_angle);
	range.y_max = max_y(y_player, y_size_game, ray_angle);
	create_possibility(all, range);
	find_winner_surface(all);
	winner = NULL;
	temp_pos = all->possible;
	if (same(ray_angle, 90) || same(ray_angle, 270))
	{
		if (same(ray_angle, 270))
		{
			while (temp_pos)
			{
				if (temp_pos->sn_winner_texture == 'S' && same_double(temp_pos->sn_winner_x, all->x))
				{
					if (!winner)
						winner = temp_pos;
					else if (temp_pos->sn_winner_distance < winner->sn_winner_distance)
						winner = temp_pos;
				}
				temp_pos = temp_pos->next;
			}
			winner_material = 'S';
		}
		else
		{
			while (temp_pos)
			{
				if (temp_pos->sn_winner_texture == 'N' && same_double(temp_pos->sn_winner_x, all->x))
				{
					if (!winner)
						winner = temp_pos;
					else if (temp_pos->sn_winner_distance < winner->sn_winner_distance)
						winner = temp_pos;
				}
				temp_pos = temp_pos->next;
			}
			winner_material = 'N';			
		}
		intersection_distance = winner->sn_winner_distance;

	}
	else if (same(ray_angle, 0) || same(ray_angle, 180))
	{
		if (same(ray_angle, 0))
		{
			while (temp_pos)
			{
				if (temp_pos->ew_winner_texture == 'W' && same_double(temp_pos->ew_winner_y, all->y))
				{
					if (!winner)
						winner = temp_pos;
					else if (temp_pos->ew_winner_distance < winner->ew_winner_distance)
						winner = temp_pos;
				}
				temp_pos = temp_pos->next;
			}
			winner_material = 'W';
		}
		else
		{
			while (temp_pos)
			{
				if (temp_pos->ew_winner_texture == 'E' && same_double(temp_pos->ew_winner_y, all->y))
				{
					if (!winner)
						winner = temp_pos;
					else if (temp_pos->ew_winner_distance < winner->ew_winner_distance)
						winner = temp_pos;
				}
				temp_pos = temp_pos->next;
			}
			winner_material = 'E';
		}
		intersection_distance = winner->ew_winner_distance;
	}
	else
	{
		while (temp_pos)
		{
			if (fabs(find_y(ray_angle, all->x, all->y, temp_pos->ew_winner_x) - temp_pos->ew_winner_y) < 1)
			{
				if (!winner)
					winner = temp_pos;
				else if (temp_pos->ew_winner_distance < winner->ew_winner_distance)
					winner = temp_pos;
				winner_material = winner->ew_winner_texture;
			}
			else if (fabs(find_x(ray_angle, all->x, all->y, temp_pos->sn_winner_y) - temp_pos->sn_winner_x) < 1)
			{
				if (!winner)
					winner = temp_pos;
				else if (temp_pos->sn_winner_distance < winner->sn_winner_distance)
					winner = temp_pos;
				winner_material = winner->sn_winner_texture;
			}
			temp_pos = temp_pos->next;
		}
	}
	if (winner_material == winner->ew_winner_texture)
		intersection_distance = distance(all->x, all->y, winner->ew_winner_x, find_y(ray_angle, all->x, all->y, winner->ew_winner_x));
	else
		intersection_distance = distance(all->x, all->y, find_x(ray_angle, all->x, all->y, winner->sn_winner_y), winner->sn_winner_y);
	
	if (intersection_distance < 0.5)
		intersection_distance = 0.5;
	clean_possibility(all->possible);
	all->possible = NULL;
	return (intersection_distance);
}

double find_left_distance(t_all *all)
{
	// t_loc		*temp_loc;
	// double		temp_x;
	// double		temp_y;
	double		x_player;
	double		y_player;
	double		angle_player;
	double		temp_angle;
	double		ray_angle;
	int 		x_size_game;
	int 		y_size_game;
	// int			x_min;
	// int			x_max;
	// int			y_min;
	// int			y_max;
	// double		temp_x_min;
	// double		temp_y_min;
	// double		temp_x_max;
	// double		temp_y_max;
	// int 		i;
	// double 		max_d;
	// char 		type_intersection;
	// double 		winner_distance;
	// double		temp_dis;
	double		intersection_distance;
	t_range		range;
	t_possible *temp_pos;
	t_possible	*winner;
	char		winner_material;

	x_player = all->x;
	y_player = all->y;
	angle_player = all->angle;
	x_size_game = all->map_width;
	y_size_game = all->map_height;
	// max_d = all->max_distance;
	temp_angle = 0;
	ray_angle = under_full_circle(angle_player - (HAOV / 2) + temp_angle);
	intersection_distance = 0;
	// temp_x_min = min_x(x_player, ray_angle);
	// temp_x_max = max_x(x_player, x_size_game, ray_angle);
	// temp_y_min = min_y(y_player, ray_angle);
	// temp_y_max = max_y(y_player, y_size_game, ray_angle);
	// printf("temp_min_x: %f, temp_y_min: %f, temp_x_max:%f, temp_y_max:%f\n", temp_x_min, temp_y_min, temp_x_max, temp_y_max);
	// // winner_distance = max_d;
	// if (same(temp_x_min, 0))
	// {
	// 	range.x_min = 0;
	// 	range.x_max = ceil(x_player);
	// }
	// else
	// {
	// 	range.x_min = floor(temp_x_min);
	// 	range.x_max = all->map_width - 1;
	// }
	// if (same(temp_y_min , 0))
	// {
	// 	range.y_min = 0;
	// 	range.y_max = ceil(y_player);
	// }
	// else
	// {
	// 	range.y_min = floor(range.x_min);
	// 	range.y_max = all->map_height - 1;
	// }
	// printf("min_x: %d, y_min: %d, x_max:%d, y_max:%d\n", range.x_min, range.y_min, range.x_max, range.y_max);
	range.x_min = min_x(x_player, ray_angle);
	range.x_max = max_x(x_player, x_size_game, ray_angle);
	range.y_min = min_y(y_player, ray_angle);
	range.y_max = max_y(y_player, y_size_game, ray_angle);
	create_possibility(all, range);
	find_winner_surface(all);
	winner = NULL;
	temp_pos = all->possible;
	if (same(ray_angle, 90) || same(ray_angle, 270))
	{
		if (same(ray_angle, 270))
		{
			while (temp_pos)
			{
				if (temp_pos->sn_winner_texture == 'S' && same_double(temp_pos->sn_winner_x, all->x))
				{
					if (!winner)
						winner = temp_pos;
					else if (temp_pos->sn_winner_distance < winner->sn_winner_distance)
						winner = temp_pos;
				}
				temp_pos = temp_pos->next;
			}
			winner_material = 'S';
		}
		else
		{
			while (temp_pos)
			{
				if (temp_pos->sn_winner_texture == 'N' && same_double(temp_pos->sn_winner_x, all->x))
				{
					if (!winner)
						winner = temp_pos;
					else if (temp_pos->sn_winner_distance < winner->sn_winner_distance)
						winner = temp_pos;
				}
				temp_pos = temp_pos->next;
			}
			winner_material = 'N';			
		}
		intersection_distance = winner->sn_winner_distance;

	}
	else if (same(ray_angle, 0) || same(ray_angle, 180))
	{
		if (same(ray_angle, 0))
		{
			while (temp_pos)
			{
				if (temp_pos->ew_winner_texture == 'W' && same_double(temp_pos->ew_winner_y, all->y))
				{
					if (!winner)
						winner = temp_pos;
					else if (temp_pos->ew_winner_distance < winner->ew_winner_distance)
						winner = temp_pos;
				}
				temp_pos = temp_pos->next;
			}
			winner_material = 'W';
		}
		else
		{
			while (temp_pos)
			{
				if (temp_pos->ew_winner_texture == 'E' && same_double(temp_pos->ew_winner_y, all->y))
				{
					if (!winner)
						winner = temp_pos;
					else if (temp_pos->ew_winner_distance < winner->ew_winner_distance)
						winner = temp_pos;
				}
				temp_pos = temp_pos->next;
			}
			winner_material = 'E';
		}
		intersection_distance = winner->ew_winner_distance;
	}
	else
	{
		while (temp_pos)
		{
			if (fabs(find_y(ray_angle, all->x, all->y, temp_pos->ew_winner_x) - temp_pos->ew_winner_y) < 1)
			{
				if (!winner)
					winner = temp_pos;
				else if (temp_pos->ew_winner_distance < winner->ew_winner_distance)
					winner = temp_pos;
				winner_material = winner->ew_winner_texture;
			}
			else if (fabs(find_x(ray_angle, all->x, all->y, temp_pos->sn_winner_y) - temp_pos->sn_winner_x) < 1)
			{
				if (!winner)
					winner = temp_pos;
				else if (temp_pos->sn_winner_distance < winner->sn_winner_distance)
					winner = temp_pos;
				winner_material = winner->sn_winner_texture;
			}
			temp_pos = temp_pos->next;
		}
	}
	if (winner_material == winner->ew_winner_texture)
		intersection_distance = distance(all->x, all->y, winner->ew_winner_x, find_y(ray_angle, all->x, all->y, winner->ew_winner_x));
	else
		intersection_distance = distance(all->x, all->y, find_x(ray_angle, all->x, all->y, winner->sn_winner_y), winner->sn_winner_y);
	
	if (intersection_distance < 0.5)
		intersection_distance = 0.5;
	clean_possibility(all->possible);
	all->possible = NULL;
	return (intersection_distance);
}


void	size_grid(t_all *all)
{
	// t_loc		*temp_loc;
	// double		temp_x;
	// double		temp_y;
	double		x_player;
	double		y_player;
	double		angle_player;
	double		temp_angle;
	double		ray_angle;
	int 		x_size_game;
	int 		y_size_game;
	// int			x_min;
	// int			x_max;
	// int			y_min;
	// int			y_max;
	// double		temp_x_min;
	// double		temp_y_min;
	// double		temp_x_max;
	// double		temp_y_max;
	// int 		i;
	// double 		max_d;
	// char 		type_intersection;
	// double 		winner_distance;
	t_render	data_rander;
	double 		distance_left;
	double 		distance_right;
	int			counter;
	// double		temp_dis;
	double		intersection_distance;
	t_range		range;
	t_possible *temp_pos;
	t_possible	*winner;
	char		winner_material;
	int change_formule = 0;

	x_player = all->x;
	y_player = all->y;
	angle_player = all->angle;
	x_size_game = all->map_width;
	y_size_game = all->map_height;
	// max_d = all->max_distance;
	temp_angle = 0;
	counter = 0;
	distance_left = find_left_distance(all);
	distance_right = find_right_distance(all);
	while (counter <= NLOOP)
	{
		ray_angle = under_full_circle(angle_player - (HAOV / 2) + temp_angle);
		intersection_distance = 0;
		// temp_x_min = min_x(x_player, ray_angle);
		// temp_x_max = max_x(x_player, x_size_game, ray_angle);
		// temp_y_min = min_y(y_player, ray_angle);
		// temp_y_max = max_y(y_player, y_size_game, ray_angle);
		// printf("temp_min_x: %f, temp_y_min: %f, temp_x_max:%f, temp_y_max:%f\n", temp_x_min, temp_y_min, temp_x_max, temp_y_max);
		// // winner_distance = max_d;
		// if (same(temp_x_min, 0))
		// {
		// 	range.x_min = 0;
		// 	range.x_max = ceil(x_player);
		// }
		// else
		// {
		// 	range.x_min = floor(temp_x_min);
		// 	range.x_max = all->map_width - 1;
		// }
		// if (same(temp_y_min , 0))
		// {
		// 	range.y_min = 0;
		// 	range.y_max = ceil(y_player);
		// }
		// else
		// {
		// 	range.y_min = floor(range.x_min);
		// 	range.y_max = all->map_height - 1;
		// }
		// printf("min_x: %d, y_min: %d, x_max:%d, y_max:%d\n", range.x_min, range.y_min, range.x_max, range.y_max);
		range.x_min = min_x(x_player, ray_angle);
		range.x_max = max_x(x_player, x_size_game, ray_angle);
		range.y_min = min_y(y_player, ray_angle);
		range.y_max = max_y(y_player, y_size_game, ray_angle);
		create_possibility(all, range);
		find_winner_surface(all);
		winner = NULL;
		temp_pos = all->possible;
		if (same(ray_angle, 90) || same(ray_angle, 270))
		{
			if (same(ray_angle, 270))
			{
				while (temp_pos)
				{
					if (temp_pos->sn_winner_texture == 'S' && same_double(temp_pos->sn_winner_x, all->x))
					{
						if (!winner)
							winner = temp_pos;
						else if (temp_pos->sn_winner_distance < winner->sn_winner_distance)
							winner = temp_pos;
					}
					temp_pos = temp_pos->next;
				}
				winner_material = 'S';
			}
			else
			{
				while (temp_pos)
				{
					if (temp_pos->sn_winner_texture == 'N' && same_double(temp_pos->sn_winner_x, all->x))
					{
						if (!winner)
							winner = temp_pos;
						else if (temp_pos->sn_winner_distance < winner->sn_winner_distance)
							winner = temp_pos;
					}
					temp_pos = temp_pos->next;
				}
				winner_material = 'N';			
			}
			intersection_distance = winner->sn_winner_distance;

		}
		else if (same(ray_angle, 0) || same(ray_angle, 180))
		{
			if (same(ray_angle, 0))
			{
				while (temp_pos)
				{
					if (temp_pos->ew_winner_texture == 'W' && same_double(temp_pos->ew_winner_y, all->y))
					{
						if (!winner)
							winner = temp_pos;
						else if (temp_pos->ew_winner_distance < winner->ew_winner_distance)
							winner = temp_pos;
					}
					temp_pos = temp_pos->next;
				}
				winner_material = 'W';
			}
			else
			{
				while (temp_pos)
				{
					if (temp_pos->ew_winner_texture == 'E' && same_double(temp_pos->ew_winner_y, all->y))
					{
						if (!winner)
							winner = temp_pos;
						else if (temp_pos->ew_winner_distance < winner->ew_winner_distance)
							winner = temp_pos;
					}
					temp_pos = temp_pos->next;
				}
				winner_material = 'E';
			}
			intersection_distance = winner->ew_winner_distance;
		}
		else
		{
			while (temp_pos)
			{
				// if (same(all->angle, 330))
				// {
				// 	printf("***************************\n");
				// 	printf("angle: %f\n", ray_angle);
				// 	printf("x_player: %f, y_player: %f\n", all->x, all->y);
				// 	printf("find_y(ray_angle, all->x, all->y, 4): %f\n", find_y(ray_angle, all->x, all->y, 4.0));
				// 	printf("find_y(ray_angle, all->x, all->y, 5): %f\n", find_y(ray_angle, all->x, all->y, 5.0));
				// 	printf("find_y(ray_angle, all->x, all->y, 6): %f\n", find_y(ray_angle, all->x, all->y, 6.0));
				// 	printf("find_x(ray_angle, all->x, all->y, 4): %f\n", find_x(ray_angle, all->x, all->y, 4.0));
				// 	printf("find_x(ray_angle, all->x, all->y, 5): %f\n", find_x(ray_angle, all->x, all->y, 5.0));
				// 	printf("find_x(ray_angle, all->x, all->y, 6): %f\n", find_x(ray_angle, all->x, all->y, 6.0));
				// 	printf("min_x: %d, max_x: %d, min_y: %d, max_y: %d\n", range.x_min, range.x_max, range.y_min, range.y_max);
				// 	printf("(%d,%d)temp_pos->ew_winner_x: %f, temp_pos->ew_winner_y: %f, temp_pos->ew_winner_material:%c\n",temp_pos->loc->x, temp_pos->loc->y,temp_pos->ew_winner_x, temp_pos->ew_winner_y, temp_pos->ew_winner_texture);
				// 	printf("fabs(find_y(ray_angle, all->x, all->y, temp_pos->ew_winner_x) - temp_pos->ew_winner_y): %f\n", fabs(find_y(ray_angle, all->x, all->y, temp_pos->ew_winner_x) - temp_pos->ew_winner_y));
				// 	printf("find_y(ray_angle, all->x, all->y, temp_pos->ew_winner_x): %f\n", find_y(ray_angle, all->x, all->y, temp_pos->ew_winner_x));
				// 	printf("(%d,%d)temp_pos->sn_winner_x: %f, temp_pos->sn_winner_y: %f,temp_pos->ew_winner_material:%c\n",temp_pos->loc->x,temp_pos->loc->y, temp_pos->sn_winner_x, temp_pos->sn_winner_y, temp_pos->sn_winner_texture);
				// 	printf("fabs(find_x(ray_angle, all->x, all->y, temp_pos->sn_winner_y) - temp_pos->sn_winner_x): %f\n", fabs(find_x(ray_angle, all->x, all->y, temp_pos->sn_winner_y) - temp_pos->sn_winner_x));
				// 	printf("find_x(ray_angle, all->x, all->y, temp_pos->sn_winner_y): %f\n", find_x(ray_angle, all->x, all->y, temp_pos->sn_winner_y));
				// }
				if (temp_pos->ew_winner_texture != '0' && fabs(find_y(ray_angle, all->x, all->y, temp_pos->ew_winner_x) - temp_pos->ew_winner_y) <= 0.5)
				{
					// if (same(all->angle, 330))						
					// 	printf("we have a winner in first if\n");
					if (!winner)
						winner = temp_pos;
					else if (temp_pos->ew_winner_distance < winner->ew_winner_distance)
					{
						// if (same(all->angle, 330))
						// 	printf("we have a real winner in first if\n");
						winner = temp_pos;
					}
					winner_material = winner->ew_winner_texture;
				}
				else if (temp_pos->sn_winner_texture != '0' && fabs(find_x(ray_angle, all->x, all->y, temp_pos->sn_winner_y) - temp_pos->sn_winner_x) <= 0.5)
				{
					// if (same(all->angle, 330))						
					// 	printf("we have a winner in second if\n");
					if (!winner)
						winner = temp_pos;
					else if (temp_pos->sn_winner_distance < winner->sn_winner_distance)
					{
						// if (same(all->angle, 330))
						// 	printf("we have a real winner in second if\n");
						winner = temp_pos;
					}
					winner_material = winner->sn_winner_texture;
				}
				temp_pos = temp_pos->next;
			}
		}
		if (winner_material == winner->ew_winner_texture)
			intersection_distance = distance(all->x, all->y, winner->ew_winner_x, find_y(ray_angle, all->x, all->y, winner->ew_winner_x));
		else
			intersection_distance = distance(all->x, all->y, find_x(ray_angle, all->x, all->y, winner->sn_winner_y), winner->sn_winner_y);
		// if (same(all->angle, 330))
		// 	printf("intersection_distance: %f for ray_angle:%f and winner_material:   %c\n", intersection_distance, ray_angle, winner_material);
		if (intersection_distance < 0.5)
			intersection_distance = 0.5;
		// printf("distance_left: %f, distance_right: %f\n", distance_left, distance_right);
		// if (temp_angle >= 0 && temp_angle <= 90)
		// 	intersection_distance = intersection_distance * fabs(ft_sin(temp_angle));
		// else
		// 	intersection_distance = intersection_distance * fabs(ft_sin(temp_angle));
		// if (same(temp_angle, 0))
		// 	distance_left = intersection_distance;
		// distance_right = find_right_distance(all);
		// if (temp_angle >= 0 && temp_angle <= 90)
		// 	intersection_distance = intersection_distance * fabs(ft_sin(temp_angle)) + distance_left;
		// else
		// 	intersection_distance = intersection_distance * fabs(ft_sin(temp_angle)) + distance_right;
		
		if (!change_formule)
			intersection_distance = intersection_distance * fabs(ft_sin(temp_angle)) + distance_left;
		else
			intersection_distance = intersection_distance * fabs(ft_sin(temp_angle)) + distance_right;
		if ((intersection_distance * fabs(ft_sin(temp_angle)) + distance_left)
			== (intersection_distance * fabs(ft_sin(temp_angle)) + distance_right))
			change_formule = 1;
		// if (temp_angle >= 0 && temp_angle <= 90)
		// 	intersection_distance = intersection_distance * fabs(ft_sin(temp_angle)) + distance_left;
		// else
		// 	intersection_distance = intersection_distance * fabs(ft_sin(temp_angle)) + distance_right;
		// if (same(all->angle, 330))
		// 	printf("intersection_distance: %f for ray_angle:%f\n", intersection_distance, ray_angle);
		data_rander.wall_texture = winner_material;
		data_rander.floor_height = height(intersection_distance, 'F');
		data_rander.ceil_height = height(intersection_distance, 'C');
		data_rander.wall_height = WINDOW_HEIGHT - data_rander.ceil_height - data_rander.floor_height;
		data_rander.x = (int)(temp_angle / WIDTH_INTERVAL);
		create_strip(all, data_rander);
		counter++;
		temp_angle+= WIDTH_INTERVAL;
		clean_possibility(all->possible);
		all->possible = NULL;
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
	ft_memset(all, 0, sizeof(t_all));
	all->argv = argv[1];
	all->fd = -1;
	all->map = map_parser(all);
	all->strip = NULL;
	all->floor_color = color_maker(all, 'f');
	all->ceil_color = color_maker(all, 'c');
	all->x = start_loc_player(all, 'x');
	all->y = start_loc_player(all, 'y');
	all->angle = start_angle_player(all);
	all->max_distance = max_distance(all);	
	all->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT,	argv[0], false);
	all->north = image_maker(all, 'N');
	all->west = image_maker(all, 'W');
	all->south = image_maker(all, 'S');
	all->east = image_maker(all, 'E');
	if (!all->window)
		terminate(all, 1);
	render(all);
	mlx_key_hook(all->window, &press_key, all);	
	mlx_loop(all->window);
	terminate(all, 0);
}
