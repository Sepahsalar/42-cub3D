/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:43:59 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/06 15:33:29 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// add deleting mlx42 in makefile

// remember to delete render at the end (not clean,
// delete it since we do not need it anymore)

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
		// return (floor(WINDOW_HEIGHT * target_height / (2 * half_full_height)));
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
		// // printf("before if: temp_loc->x_mid:%f, x_max:%f, x_min:%f, temp_loc->c:%c\n", temp_loc->x_mid, x_max, x_min, temp_loc->c);
		if (temp_loc->y_mid == y_player && temp_loc->x_mid <= x_max && temp_loc->x_mid >= x_min && temp_loc->c == '1')
		{
			// // printf("after first if : temp_loc->x_mid:%f, x_max:%f, x_min:%f, temp_loc->c:%c\n", temp_loc->x_mid, x_max, x_min, temp_loc->c);
			if (fabs(temp_loc->x_mid - x_player) < temp_distance)
			{
				// // printf("temp_loc->x_mid:%f, x_player:%f\n", temp_loc->x_mid, x_player);
				temp_distance = fabs(temp_loc->x_mid - x_player);
			}
		}
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
	double		final_x;
	double		final_y;
	double 		distance_left;
	double 		distance_right;

	x_player = start_loc_player(all, 'x');
	y_player = start_loc_player(all, 'y');
	angle_player = start_angle_player(all);
	x_size_game = game_size(all, 'x');
	y_size_game = game_size(all, 'y');
	max_d = max_distance(all);
	(void)all;
	temp_angle = 0;
	int counter;
	counter = 0;

	// printf("*************************************************\n\n\n");
	// while (temp_angle <= (double)HAOV)
	while (counter <= NLOOP)
	{
		ray_angle = angle_player - (HAOV / 2) + temp_angle;
		x_min = min_x(x_player, ray_angle);
		x_max = max_x(x_player, x_size_game, ray_angle);
		y_min = min_y(y_player, ray_angle);
		y_max = max_y(y_player, y_size_game, ray_angle);
		temp_distance = max_d;
		i = x_min;
		// // printf("y = %f(x - %f) + %f\n", ft_tan(ray_angle), x_player, y_player);
		// // printf("ray_angle:%f, x_min:%f, x_max:%f, y_min:%f, y_max:%f\n", ray_angle, x_min, x_max, y_min, y_max);
		if (ceil(ray_angle) == floor(ray_angle) && (int)ray_angle % 180 == 90)
		{
			temp_loc = all->map->start;
			while (temp_loc)
			{
				if (temp_loc->x_mid == x_player && temp_loc->y_mid <= y_max && temp_loc->y_mid >= y_min && temp_loc->c == '1')
				{
					// if ((int)ray_angle % 360 == 270 && abs(temp_loc->y1 - y_player) < temp_distance)
					if (fabs(temp_loc->y_mid - y_player) < temp_distance)
					{
						temp_distance = fabs(temp_loc->y_mid - y_player);
						final_x = temp_loc->x;
						final_y = temp_loc->y;
						type_intersection = 'y';
						// // printf("from first loop : type: %c, final_x:%f, final_y:%f , temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
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
						final_x = temp_loc->x;
						final_y = temp_loc->y;
						type_intersection = 'x';
						// // printf("from second loop : type: %c, final_x:%f, final_y:%f , temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
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
					// // printf("for x: %d, temp_y:%f\n", i,temp_y);
				while (temp_loc)
				{
					if (temp_loc->x0 <= i && i <= temp_loc->x1 && temp_loc->y0 <= temp_y &&  temp_y <= temp_loc->y1 && temp_loc->c == '1')
					{
						// printf("temp_loc->x:%d , temp_loc->y:%d, temp_loc_x_range(x0:%d,x1:%d), temp_loc_y_range(y0:%d,y1:%d)\n", temp_loc->x, temp_loc->y, temp_loc->x0, temp_loc->x1, temp_loc->y0, temp_loc->y1);
						// printf("distance in first loop for intersection (x:%d and y:%f) and player(%f, %f) is %f\n", i, temp_y , x_player, y_player, distance((double)i, temp_y, x_player, y_player));
						if (distance((double)i, temp_y, x_player, y_player) < temp_distance)
						// if (distance((double)temp_loc->x, (double)temp_loc->y, x_player, y_player) < temp_distance)
						{
							temp_distance = distance((double)i, temp_y, x_player, y_player);
							// temp_distance = distance((double)temp_loc->x, (double)temp_loc->y, x_player, y_player);
							final_x = temp_loc->x;
							final_y = temp_loc->y;
							type_intersection = 'x';
							// printf("from first loop : type: %c, final_x:%f, final_y:%f , temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
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
				// // printf("for y: %d, temp_x:%f\n", i, temp_x);
				while (temp_loc)
				{
				// // printf("temp_loc->y0:%d, i:%d, temp_loc->y1:%d, temp_x:%f, temp_loc->x0:%d, temp_loc->x1:%d, temp_loc->c:%c\n", temp_loc->y0, i, temp_loc->y1, temp_x, temp_loc->x0, temp_loc->x1, temp_loc->c);
					if (temp_loc->y0 <= i && i <= temp_loc->y1 && temp_loc->x0 <= temp_x && temp_x <= temp_loc->x1 && temp_loc->c == '1')
					{
						// printf("distance in second loop for intersection (x:%f and y:%d) and player(%f, %f) is %f\n", temp_x, i , x_player, y_player, distance(temp_x, (double)i, x_player, y_player));
						if (distance(temp_x, (double)i, x_player, y_player) < temp_distance)
						// if (distance((double)temp_loc->x, (double)temp_loc->y, x_player, y_player) < temp_distance)
						{
							// temp_distance = distance((double)temp_loc->x, (double)temp_loc->y, x_player, y_player);
							temp_distance = distance(temp_x, (double)i, x_player, y_player);
							final_x = temp_loc->x;
							final_y = temp_loc->y;
							type_intersection = 'y';
							// printf("from second loop : type: %c, final_x:%f, final_y:%f , temp_distance: %f\n",type_intersection, final_x, final_y, temp_distance);
						}
					}
					temp_loc = temp_loc->next;
				}
				i++;
			}
		}
		// printf("final_x:%f, final_y:%f\n", final_x, final_y);
		// printf("before sinus: temp_distance:%f\n", temp_distance);
		// distance_left = 0;
		if (temp_angle == 0)
			distance_left = temp_distance;
		distance_right = find_right_distance(all);
		// // printf("distance_left:%f, distance_right:%f\n", distance_left, distance_right);
		if (temp_angle >= 0 && temp_angle <= 90)
			temp_distance = temp_distance * fabs(ft_sin(temp_angle)) + distance_left;
		else
			// temp_distance = distance_right - (temp_distance * fabs(ft_sin(temp_angle)));
			temp_distance = temp_distance * fabs(ft_sin(temp_angle)) + distance_right;
		// // printf("after sinus: temp_distance:%f\n", temp_distance);
		data_rander.wall_texture = wall_selection(ray_angle, type_intersection);
		data_rander.ceil_height = height(temp_distance, 'C');
		data_rander.floor_height = height(temp_distance, 'F');
		data_rander.wall_height = WINDOW_HEIGHT - data_rander.ceil_height - data_rander.floor_height;
		data_rander.x = (int)(temp_angle / WIDTH_INTERVAL);
		// {
		// 	// printf("temp_angle:%f, ray_angle: %f, temp_distance:%f, wall_texture:%c, ceil_height:%d, floor_height:%d, wall_height:%d, x:%d\n", temp_angle, ray_angle, temp_distance, data_rander.wall_texture, data_rander.ceil_height, data_rander.floor_height, data_rander.wall_height, data_rander.x);
		// 	// printf("\n\n");
		// }
		create_render(all, data_rander);
		create_strip(all, data_rander);
		// // printf("temp_angle:%f\n", temp_angle);
		counter++;
		temp_angle+= WIDTH_INTERVAL;
	}
	// // printf("temp_angle:%f\n", temp_angle);
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
	all->strip = NULL;
	all->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT,	argv[0], false);
	if (!all->window)
		terminate(all, 1);
	size_grid(all);
	fill_index_strip(all);
	fill_length_strip(all);
	create_elements(all);
	
	all->display = malloc(sizeof(t_display));
	if(!all->display)
		terminate(all, 1);
	all->display->wall = NULL;
	all->display->floor = NULL;
	all->display->ceil = NULL;
	strip_to_wall(all);
	strip_to_floor(all);
	// printf("image height: %d, image width: %d\n", all->elems->f->height, all->elems->f->width);
	strip_to_ceil(all);
	create_instance(all);
	// mlx_resize_image(all->elems->f, WINDOW_WIDTH/2, WINDOW_HEIGHT);
	// mlx_image_to_window(all->window, all->elems->f, 0, 0);
	// int i = 0;
	// int j = 0;
	// printf("image height: %d, image width: %d\n", all->elems->f->height, all->elems->f->width);
	// while (i < WINDOW_WIDTH/2)
	// {
	// 	j = 0;
	// 	while (j < 1)
	// 	{
	// 		mlx_image_to_window(all->window, all->elems->f, i, j);
	// 		printf("image height: %d, image width: %d\n", all->elems->f->height, all->elems->f->width);
	// 		j++;
	// 	}
	// 	i++;
	// }
		
	
	
	// t_loc *temp;
	// temp = all->render; // 
	// int x = 0;
	// int y = 0;
	// while (y <= WINDOW_HEIGHT)
	// {
	// 	x = 0;
	// 	while (x <= WINDOW_WIDTH)
	// 	{
	// 		temp = all->render;
	// 		while (temp)
	// 		{
	// 			if (temp->x == x && temp->y == y)
	// 				break;
	// 			temp = temp->next;
	// 		}
	// 		if (temp)
	// 			// printf("%c",temp->c);
	// 		x++;
	// 	}
	// 	// printf("\n");
	// 	y++;
	// }
	mlx_loop(all->window);
	terminate(all, 0);
}
