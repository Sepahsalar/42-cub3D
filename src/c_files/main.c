/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:43:59 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/24 13:17:17 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"


double ft_tan(double a)
{
	double angle;

	angle = M_PI * a / 180;
	return (tan(angle));
}

double find_y(double angle, int x_player, int y_player, int x_target)
{
	double	y_target;

	y_target = ((x_target - x_player) * ft_tan(angle)) + y_player;
	return (y_target);
	
}

double find_x(double angle, int x_player, int y_player, int y_target)
{
	double	x_target;

	x_target = ((y_target - y_player) / ft_tan(angle)) + x_player;
	return (x_target);
	
}

double distance(double x1, double y1, int x2, int y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

int min_x(int x_player, double angle)
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

int max_x(int x_player, int x_game_size, double angle)
{
	while (angle < 0)
		angle = angle + FULL_CIRCLE_DEGREES;
	if (angle >= 0 && angle <= FULL_CIRCLE_DEGREES / 4)
		return(x_game_size - 1);
	else if (angle > FULL_CIRCLE_DEGREES / 4
		&& angle <= FULL_CIRCLE_DEGREES * 3 / 4)
		return (x_player);
	else
		return (x_game_size - 1);
}

int min_y(int y_player, double angle)
{
	while (angle < 0)
		angle = angle + FULL_CIRCLE_DEGREES;
	if (angle >= 0 && angle <= FULL_CIRCLE_DEGREES * 3 / 4)
		return(y_player);
	else
		return (0);
}

int max_y(int y_player, int y_game_size, double angle)
{
	while (angle < 0)
		angle = angle + FULL_CIRCLE_DEGREES;
	if (angle >= 0 && angle <= FULL_CIRCLE_DEGREES * 3 / 4)
		return(y_game_size - 1);
	else
		return (y_player);
}

int start_loc_player(t_all *all, char c)
{
	t_loc *loc;

	loc = all->map->start;
	while (loc)
	{
		if (loc->c == 'N' || loc->c == 'S' || loc->c == 'W' || loc->c == 'E')
		{
			if (c == 'x')
				return (loc->x);
			else
				return (loc->y);
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
				return ((double)90);
			else if (loc->c == 'S')
				return ((double)270);
			else if (loc->c == 'W')
				return ((double)180);
			else
				return ((double)0);
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
	int x;
	int	y;

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
	if (angle >= 0 && angle <= FULL_CIRCLE_DEGREES / 4)
		return (wall_helper(c, 'W', 'S'));
	else if (angle > FULL_CIRCLE_DEGREES / 4
		&& angle <= FULL_CIRCLE_DEGREES / 2)
		return (wall_helper(c, 'E', 'S'));
	else if (angle > FULL_CIRCLE_DEGREES / 2
		&& angle <= FULL_CIRCLE_DEGREES * 3 / 4)
		return (wall_helper(c, 'E', 'N'));
	else
		return (wall_helper(c, 'W', 'N'));
}

char *get_texture(t_all *all, char c)
{
	if (c == 'N')
		return (all->map->north);
	else if (c == 'S')
		return (all->map->south);
	else if (c == 'W')
		return (all->map->west);
	else
		return (all->map->east);
}

char *get_color(t_all *all, char c)
{
	if (c == 'F')
		return (all->map->floor);
	else
		return (all->map->ceil);
}

char *get_texture_color(t_all *all, double angle, char c)
{
	char *texture;
	char *color;

	texture = get_texture(all, wall_selection(angle, c));
	color = get_color(all, c);
	if (texture)
		return (texture);
	else
		return (color);
}

void	size_grid(t_all *all)
{
	// t_loc *loc;
	t_loc *temp_loc;
	// int x;
	// int y;
	// int angle;
	// double angle_rad;
	double temp_x;
	double temp_y;
	// double min_d;
	// double final_x;
	// double final_y;

	int x_player;
	int y_player;
	double angle_player;
	double temp_angle;
	double ray_angle;
	int 	x_size_game;
	int 	y_size_game;
	int 	x_min;
	int 	x_max;
	int 	y_min;
	int 	y_max;
	int 	i;
	double 	max_d;
	char 	type_intersection;
	double 	temp_distance;
	char wall;

	x_player = start_loc_player(all, 'x');
	y_player = start_loc_player(all, 'y');
	angle_player = start_angle_player(all);
	x_size_game = game_size(all, 'x');
	y_size_game = game_size(all, 'y');
	max_d = max_distance(all);
	temp_angle = 0;
	while (temp_angle < HAOV)
	{
		ray_angle = angle_player + (HAOV / 2) - temp_angle;
		x_min = min_x(x_player, ray_angle);
		x_max = max_x(x_player, x_size_game, ray_angle);
		y_min = min_y(y_player, ray_angle);
		y_max = max_y(y_player, y_size_game, ray_angle);
		temp_distance = max_d;
		i = x_min;
		while (i < x_max)
		{
			temp_loc = all->map->start;
			temp_y = find_y(ray_angle, x_player, y_player, i);
			while (temp_loc)
			{
				if (temp_loc->x == i && temp_loc->y <= ceil(temp_y) && temp_loc->y >= floor(temp_y) && temp_loc->c == '1')
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
		while(i < y_max)
		{
			temp_loc = all->map->start;
			temp_x = find_x(ray_angle, x_player, y_player, i);
			while (temp_loc)
			{
				if (temp_loc->y == i && temp_loc->x <= ceil(temp_x) && temp_loc->x >= floor(temp_x) && temp_loc->c == '1')
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
		wall = wall_selection(ray_angle, type_intersection);
		temp_angle+= WIDTH_INTERVAL;
	}
	// loc = all->map->start;
	// x = 0;
	// y = 0;
	// while (loc)
	// {
	// 	if (x < loc->x)
	// 		x = loc->x;
	// 	if (y < loc->y)
	// 		y = loc->y;
	// 	loc = loc->next;
	// }
	// printf("size of map : x = %d, y = %d\n", x + 1, y + 1);
	// loc = all->map->start;
	// while (loc)
	// {
	// 	if (loc->c == 'N' || loc->c == 'S' || loc->c == 'W' || loc->c == 'E')
	// 		break ;
	// 	loc = loc->next;
	// }
	// printf("loc of player : x = %d, y = %d\n", loc->x, loc->y);
	// angle = 45;
	// min_d = sqrt(pow(x + 1, 2) + pow(y + 1, 2));
	// // while (angle < 90)
	// // {
	// 	angle_rad = angle * M_PI / 180;
	// 	temp_x = loc->x;
	// 	while (temp_x < x + 1)
	// 	{
	// 		temp_loc = all->map->start;
	// 		temp_y = (tan((M_PI / 2) - angle_rad) * (temp_x - loc->x)) + loc->y;
	// 		while (temp_loc)
	// 		{
	// 			if (temp_loc->x == temp_x && temp_loc->y <= ceil(temp_y) && temp_loc->y >= floor(temp_y) && temp_loc->c == '1')
	// 			{
	// 				if (sqrt(pow(temp_x - loc->x, 2) + pow(temp_y - loc->y, 2)) < min_d)
	// 				{
	// 					min_d = sqrt(pow(temp_x - loc->x, 2) + pow(temp_y - loc->y, 2));
	// 					final_x = temp_loc->x;
	// 					final_y = temp_loc->y;
	// 				}
	// 			}
	// 			temp_loc = temp_loc->next;
	// 		}
			
	// 		// printf("angle = %d, for x = %f, intersection y = %f\n", angle, temp_x, temp_y);
	// 		temp_x++;
	// 	}
	// 	printf("final x = %f, final y = %f\n", final_x, final_y);
	// 	temp_y = loc->y;
	// 	min_d = sqrt(pow(x + 1, 2) + pow(y + 1, 2));
	// 	while (temp_y)
	// 	{
	// 		temp_loc = all->map->start;
	// 		temp_x = temp_y - loc->y / tan((M_PI / 2) - angle_rad) + loc->x;
	// 		while (temp_loc)
	// 		{
	// 			// printf("loc->x = %d, loc->y = %d, temp_x = %f, temp_y = %f\n", loc->x, loc->y, temp_x, temp_y);
	// 			if (temp_loc->y == temp_y && temp_loc->x <= ceil(temp_x) && temp_loc->x >= floor(temp_x) && temp_loc->c == '1')
	// 			{
	// 				if (sqrt(pow(temp_x - loc->x, 2) + pow(temp_y - loc->y, 2)) < min_d)
	// 				{
	// 					min_d = sqrt(pow(temp_x - loc->x, 2) + pow(temp_y - loc->y, 2));
	// 					final_x = temp_loc->x;
	// 					final_y = temp_loc->y;
	// 				}
	// 			}
	// 			temp_loc = temp_loc->next;
	// 		}
			
	// 		// printf("angle = %d, for y = %f, intersection x = %f\n", angle, temp_y, temp_x);
	// 		// printf("floor y = %f and ceil y = %f\n", floor(temp_y), ceil(temp_y));
	// 		temp_y--;
	// 	}
	// 	printf("final x = %f, final y = %f\n", final_x, final_y);	
	// // 	angle++;
		
	// // }
	
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
	size_grid(all);
	terminate(all, 0);
}
