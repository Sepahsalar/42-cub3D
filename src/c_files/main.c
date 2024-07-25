/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:43:59 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/25 17:49:05 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// add deleting mlx42 in makefile

// shorue partab ray az noghteie vasat
// mokhtasat player az noghteie vasat
// fasele az vasat ta noghteie brakhord

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
	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
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
	if (angle >= 0 && angle <= FULL_CIRCLE_DEGREES / 2)
		return(y_player);
	else
		return (0);
}

int max_y(int y_player, int y_game_size, double angle)
{
	while (angle < 0)
		angle = angle + FULL_CIRCLE_DEGREES;
	if (angle >= 0 && angle <= FULL_CIRCLE_DEGREES / 2)
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

int height(double distance, char c)
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
		return (floor(WINDOW_HEIGHT * target_height / (2 * half_full_height)));
}

void	size_grid(t_all *all)
{
	t_loc		*temp_loc;
	double		temp_x;
	double		temp_y;
	int			x_player;
	int			y_player;
	double		angle_player;
	double		temp_angle;
	double		ray_angle;
	int 		x_size_game;
	int 		y_size_game;
	int 		x_min;
	int 		x_max;
	int 		y_min;
	int 		y_max;
	int 		i;
	double 		max_d;
	char 		type_intersection;
	double 		temp_distance;
	t_render	data_rander;
	int			final_x;
	int			final_y;

	x_player = start_loc_player(all, 'x');
	y_player = start_loc_player(all, 'y');
	angle_player = start_angle_player(all);
	x_size_game = game_size(all, 'x');
	y_size_game = game_size(all, 'y');
	max_d = max_distance(all);
	temp_angle = 0;

	printf("*************************************************\n\n\n");
	while (temp_angle <= HAOV)
	{
		ray_angle = angle_player - (HAOV / 2) + temp_angle;
		x_min = min_x(x_player, ray_angle);
		x_max = max_x(x_player, x_size_game, ray_angle);
		y_min = min_y(y_player, ray_angle);
		y_max = max_y(y_player, y_size_game, ray_angle);
		temp_distance = max_d;
		i = x_min;
		printf("y = %f(x - %d) + %d\n", ft_tan(ray_angle), x_player, y_player);
		printf("ray_angle:%f, x_min:%d, x_max:%d, y_min:%d, y_max:%d\n", ray_angle, x_min, x_max, y_min, y_max);
		if (ceil(ray_angle) == floor(ray_angle) && (int)ray_angle % 180 == 90)
		{
			temp_loc = all->map->start;
			while (temp_loc)
			{
				if (temp_loc->x == x_player && temp_loc->y <= y_max && temp_loc->y >= y_min && temp_loc->c == '1')
				{
					// if ((int)ray_angle % 360 == 270 && abs(temp_loc->y1 - y_player) < temp_distance)
					if (abs(temp_loc->y - y_player) < temp_distance)
					{
						temp_distance = abs(temp_loc->y - y_player);
						final_x = temp_loc->x;
						final_y = temp_loc->y;
						type_intersection = 'y';
						printf("from first loop : type: %c, final_x:%d, final_y:%d , temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
					}
					// else if (abs(temp_loc->y0 - y_player) < temp_distance)
					// {
					// 	temp_distance = abs(temp_loc->y0 - y_player);
					// 	final_x = temp_loc->x;
					// 	final_y = temp_loc->y;
					// 	type_intersection = 'y';
					// 		printf("from first loop : type: %c, final_x:%d, final_y:%d , temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
					// }
				}
				temp_loc = temp_loc->next;
			}
		}
		else if (ceil(ray_angle) == floor(ray_angle) && (int)ray_angle % 180 == 0)
		{
			temp_loc = all->map->start;
			while (temp_loc)
			{
				if (temp_loc->y == y_player && temp_loc->x <= x_max && temp_loc->x >= x_min && temp_loc->c == '1')
				{
					// if ((int)ray_angle % 360 != 0 && abs(temp_loc->x1 - x_player) < temp_distance)
					if (abs(temp_loc->x - x_player) < temp_distance)
					{
						temp_distance = abs(temp_loc->x - x_player);
						final_x = temp_loc->x;
						final_y = temp_loc->y;
						type_intersection = 'x';
						printf("from first loop : type: %c, final_x:%d, final_y:%d , temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
					}
					// else if (abs(temp_loc->x0 - x_player) < temp_distance)
					// {
					// 	temp_distance = abs(temp_loc->x0 - x_player);
					// 	final_x = temp_loc->x;
					// 	final_y = temp_loc->y;
					// 	type_intersection = 'x';
					// 		printf("from first loop : type: %c, final_x:%d, final_y:%d , temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
					// }
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
					printf("for x: %d, temp_y:%f\n", i,temp_y);
				
				while (temp_loc)
				{
					// if (temp_loc->x == i && temp_loc->y <= ceil(temp_y) && temp_loc->y >= floor(temp_y) && temp_loc->c == '1')
					// {
					// 	if (distance((double)i, temp_y, x_player, y_player) < temp_distance)
					// 	{
					// 		temp_distance = distance((double)i, temp_y, x_player, y_player);
					// 		final_x = temp_loc->x;
					// 		final_y = temp_loc->y;
					// 		type_intersection = 'x';
			
					// 			printf("from first loop : type: %c, final_x:%d, final_y:%d , temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
					// 	}
					// }
					// if ((temp_loc->x == i || temp_loc->x + 1 == i) && temp_loc->y <= ceil(temp_y) && temp_loc->y >= floor(temp_y) && temp_loc->c == '1')
					// {
					// 	if (distance((double)i, temp_y, x_player, y_player) < temp_distance)
					// 	{
					// 		temp_distance = distance((double)i, temp_y, x_player, y_player);
					// 		final_x = temp_loc->x;
					// 		final_y = temp_loc->y;
					// 		type_intersection = 'x';
			
					// 			printf("from first loop : type: %c, final_x:%d, final_y:%d , temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
					// 	}
					// }
					// if (temp_loc->x == i && temp_loc->y <= ceil(temp_y) &&  floor(temp_y) <= temp_loc->y && temp_loc->c == '1')
					if (temp_loc->x0 <= i && i <= temp_loc->x1 && temp_loc->y0 <= temp_y &&  temp_y <= temp_loc->y1 && temp_loc->c == '1')
					{
						// if (distance((double)i, temp_y, x_player, y_player) < temp_distance)
						if (distance((double)temp_loc->x, (double)temp_loc->y, x_player, y_player) < temp_distance)
						{
							// temp_distance = distance((double)i, temp_y, x_player, y_player);
							temp_distance = distance((double)temp_loc->x, (double)temp_loc->y, x_player, y_player);
							final_x = temp_loc->x;
							final_y = temp_loc->y;
							type_intersection = 'x';
							printf("from first loop : type: %c, final_x:%d, final_y:%d , temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
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
				printf("for y: %d, temp_x:%f\n", i, temp_x);
				while (temp_loc)
				{
					// if (temp_loc->y == i && temp_loc->x <= ceil(temp_x) && temp_loc->x >= floor(temp_x) && temp_loc->c == '1')
					// {
					// 	if (distance(temp_x, (double)i, x_player, y_player) < temp_distance)
					// 	{
					// 		temp_distance = distance(temp_x, (double)i, x_player, y_player);
					// 		final_x = temp_loc->x;
					// 		final_y = temp_loc->y;
					// 		type_intersection = 'y';
			
					// 			printf("from second loop : type: %c, final_x:%d, final_y:%d, temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
					// 	}
					// }
					// if ((temp_loc->y == i || temp_loc->y + 1 == i) && temp_loc->x <= ceil(temp_x) && temp_loc->x >= floor(temp_x) && temp_loc->c == '1')
					// {
					// 	if (distance(temp_x, (double)i, x_player, y_player) < temp_distance)
					// 	{
					// 		temp_distance = distance(temp_x, (double)i, x_player, y_player);
					// 		final_x = temp_loc->x;
					// 		final_y = temp_loc->y;
					// 		type_intersection = 'y';
			
					// 			printf("from second loop : type: %c, final_x:%d, final_y:%d, temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
					// 	}
					// }
					if (ray_angle == 300)
						printf("temp_loc->y0:%d, i:%d, temp_loc->y1:%d, temp_x:%f, temp_loc->x0:%d, temp_loc->x1:%d, temp_loc->c:%c\n", temp_loc->y0, i, temp_loc->y1, temp_x, temp_loc->x0, temp_loc->x1, temp_loc->c);
					if (temp_loc->y0 <= i && i <= temp_loc->y1 && temp_loc->x0 <= temp_x && temp_x <= temp_loc->x1 && temp_loc->c == '1')
					// if (temp_loc->y == i && temp_loc->x <= ceil(temp_x) && floor(temp_x) <= temp_loc->x && temp_loc->c == '1')
					{
						if (ray_angle == 300)
							printf("here\n");
						// if (distance(temp_x, (double)i, x_player, y_player) < temp_distance)
						if (distance((double)temp_loc->x, (double)temp_loc->y, x_player, y_player) < temp_distance)
						{
							temp_distance = distance((double)temp_loc->x, (double)temp_loc->y, x_player, y_player);
							// temp_distance = distance(temp_x, (double)i, x_player, y_player);
							final_x = temp_loc->x;
							final_y = temp_loc->y;
							type_intersection = 'y';

								printf("from second loop : type: %c, final_x:%d, final_y:%d, temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
						}
					}
					temp_loc = temp_loc->next;
				}
				i++;
			}
		}
		printf("final_x:%d, final_y:%d\n", final_x, final_y);
		printf("before sinus: temp_distance:%f\n", temp_distance);
		temp_distance = temp_distance * fabs(ft_sin(temp_angle));
		printf("after sinus: temp_distance:%f\n", temp_distance);
		data_rander.wall_texture = wall_selection(ray_angle, type_intersection);
		data_rander.ceil_height = height(temp_distance, 'C');
		data_rander.floor_height = height(temp_distance, 'F');
		data_rander.wall_height = WINDOW_HEIGHT - data_rander.ceil_height - data_rander.floor_height;
		data_rander.x = (int)(temp_angle / WIDTH_INTERVAL);
		// {
			printf("temp_angle:%f, ray_angle: %f, temp_distance:%f, wall_texture:%c, ceil_height:%d, floor_height:%d, wall_height:%d, x:%d\n", temp_angle, ray_angle, temp_distance, data_rander.wall_texture, data_rander.ceil_height, data_rander.floor_height, data_rander.wall_height, data_rander.x);
			printf("\n\n");
		// }
		create_render(all, data_rander);
		temp_angle+= WIDTH_INTERVAL;
	}
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
	all->render = NULL;
	// all->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT,	argv[0], false);
	// all->elems = create_elements(all);
	size_grid(all);
	// t_loc *temp;
	// // temp = all->render;
	// // while (temp)
	// // {
	// // 	printf("x:%d, y:%d, material:%c\n", temp->x, temp->y, temp->c);
	// // 	temp = temp->next;
	// // }
	// int x = 0;
	// int y = 0;
	// while (y < WINDOW_HEIGHT)
	// {
	// 	x = 0;
	// 	while (x < WINDOW_WIDTH)
	// 	{
	// 		temp = all->render;
	// 		while (temp)
	// 		{
	// 			// printf("x:%d, y:%d, material:%c\n", temp->x, temp->y, temp->c);
	// 			if (temp->x == x && temp->y == y)
	// 				break;
	// 			temp = temp->next;
	// 		}
	// 		if (temp)
	// 			printf("%c",temp->c);
	// 		x++;
	// 	}
	// 	printf("\n");
	// 	y++;
	// }
	terminate(all, 0);
}
