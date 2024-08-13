/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:43:59 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/13 17:40:56 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
	if (angle >= 0 && angle < FULL_CIRCLE_DEGREES / 2)
		return(y_player);
	else
		return (0);
}

double max_y(double y_player, int y_game_size, double angle)
{
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

t_winner	find_general_intersection(t_all *all, double ray_angle)
{
	t_possible	*temp_pos;
	t_possible	*winner;
	t_winner	final;
	char		winner_material;
	
	temp_pos = all->possible;
	winner = NULL;
	winner_material = '0';
	while (temp_pos)
	{
		if (temp_pos->ew_winner_texture != '0' && fabs(find_y(ray_angle, all->x, all->y, temp_pos->ew_winner_x) - temp_pos->ew_winner_y) <= 0.5)
		{
			if (!winner || ((winner_material == winner->ew_winner_texture && temp_pos->ew_winner_distance < winner->ew_winner_distance)
				|| (winner_material == winner->sn_winner_texture && temp_pos->ew_winner_distance < winner->sn_winner_distance)))
			{
				winner = temp_pos;
				winner_material = winner->ew_winner_texture;
			}
		}
		if (temp_pos->sn_winner_texture != '0' && fabs(find_x(ray_angle, all->x, all->y, temp_pos->sn_winner_y) - temp_pos->sn_winner_x) <= 0.5)
		{
			if (!winner || ((winner_material == winner->ew_winner_texture && temp_pos->sn_winner_distance < winner->ew_winner_distance)
				|| (winner_material == winner->sn_winner_texture && temp_pos->sn_winner_distance < winner->sn_winner_distance)))
			{
				winner = temp_pos;
				winner_material = winner->sn_winner_texture;
			}
		}
		temp_pos = temp_pos->next;
	}
	final.pos = winner;
	final.texture = winner_material;
	final.x_winner = winner->loc->x;
	final.y_winner = winner->loc->y;
	return (final);
}

t_winner	find_specific_intersection(t_all *all, double ray_angle, char flag)
{
	t_possible	*temp_pos;
	t_possible	*winner;
	char		winner_material;
	t_winner	final;

	temp_pos = all->possible;
	winner = NULL;
	winner_material = '0';
	if (same(ray_angle, 270) || same(ray_angle, 90))
	{
		while (temp_pos)
		{
			if (temp_pos->sn_winner_texture == flag && same_double(temp_pos->sn_winner_x, all->x))
				if (!winner || (temp_pos->sn_winner_distance < winner->sn_winner_distance))
					winner = temp_pos;
			temp_pos = temp_pos->next;
		}
		winner_material = flag;
	}
	else if (same(ray_angle, 0) || same(ray_angle, 180))
	{
		while (temp_pos)
		{
			if (temp_pos->ew_winner_texture == flag && same_double(temp_pos->ew_winner_y, all->y))
				if (!winner || (temp_pos->ew_winner_distance < winner->ew_winner_distance))
					winner = temp_pos;
			temp_pos = temp_pos->next;
		}
		winner_material = flag;
	}
	final.pos = winner;
	final.texture = winner_material;
	final.x_winner = winner->loc->x;
	final.y_winner = winner->loc->y;
	return (final);
}

double calculate_distance(t_all *all, t_winner final, double ray_angle, double temp_angle)
{
	t_possible	*winner;
	char		winner_material;
	double		intersection_distance;
	
	winner = final.pos;
	winner_material = final.texture;
	if (winner_material == winner->ew_winner_texture)
		intersection_distance = distance(all->x, all->y, winner->ew_winner_x, find_y(ray_angle, all->x, all->y, winner->ew_winner_x));
	else
		intersection_distance = distance(all->x, all->y, find_x(ray_angle, all->x, all->y, winner->sn_winner_y), winner->sn_winner_y);
	if (same(temp_angle, 0) || same(temp_angle, 180))
		printf("before sin -> for temp_angle: %f intersection_distance: %f\n", temp_angle, intersection_distance);
	if (intersection_distance < 0.5)
		intersection_distance = 0.5;
	intersection_distance = intersection_distance * fabs(ft_cos(all->angle - ray_angle)) + 0.5;
	// if (!all->distance_flag)
		// intersection_distance = intersection_distance * (ft_sin(temp_angle)) + all->left_distance;
	// else
	// 	intersection_distance = intersection_distance * (ft_sin(temp_angle)) + all->right_distance;
		// intersection_distance = fabs(all->right_distance - intersection_distance * (ft_sin(temp_angle)));

	// if (same_double((intersection_distance * fabs(ft_sin(temp_angle)) + all->left_distance),
	// 			(intersection_distance * fabs(ft_sin(temp_angle)) + all->right_distance)))
	// if (same_double((fabs(all->left_distance - all->right_distance)),0))
	// {
	// 	printf("flag changed from %d to 1\n", all->distance_flag);
	// 	all->distance_flag = 1;
	// }
	
	return (intersection_distance);
}

t_winner	find_intersection(t_all *all, double ray_angle)
{
	t_winner	final;
	
	if (same(ray_angle, 270))
		final = find_specific_intersection(all, ray_angle, 'S');
	else if (same(ray_angle, 90))
		final = find_specific_intersection(all, ray_angle, 'N');
	else if (same(ray_angle, 0))
		final = find_specific_intersection(all, ray_angle, 'W');
	else if (same(ray_angle, 180))
		final = find_specific_intersection(all, ray_angle, 'E');
	else
		final = find_general_intersection(all, ray_angle);
	return (final);
}

t_winner	find_winner(t_all *all, double ray_angle)
{
	t_range 	range;
	t_winner	final;
	
	range.x_min = min_x(all->x, ray_angle);
	range.x_max = max_x(all->x, all->map_width, ray_angle);
	range.y_min = min_y(all->y, ray_angle);
	range.y_max = max_y(all->y, all->map_height, ray_angle);
	create_possibility(all, range);
	find_winner_surface(all);
	final = find_intersection(all, ray_angle);
	clean_possibility(all->possible);
	all->possible = NULL;
	return (final);
}

double find_lateral_distance(t_all *all, char flag)
{
	double		ray_angle;
	t_winner	final;
	double		intersection_distance;
	
	if (flag == 'L')
		ray_angle = under_full_circle(all->angle - (FULL_CIRCLE_DEGREES / 4));
	else
		ray_angle = under_full_circle(all->angle + (FULL_CIRCLE_DEGREES / 4));
	final = find_winner(all, ray_angle);
	if (final.texture == final.pos->ew_winner_texture)
		intersection_distance = distance(all->x, all->y, final.pos->ew_winner_x, find_y(ray_angle, all->x, all->y, final.pos->ew_winner_x));
	else
		intersection_distance = distance(all->x, all->y, find_x(ray_angle, all->x, all->y, final.pos->sn_winner_y), final.pos->sn_winner_y);
	if (intersection_distance < 0.5)
		intersection_distance = 0.5;
	return (intersection_distance);
}

t_render create_render_data(t_winner final, double intersection_distance, double temp_angle)
{
	t_render	data_render;
	char		winner_material;

	winner_material = final.texture;
	data_render.wall_texture = winner_material;
	data_render.floor_height = height(intersection_distance, 'F');
	data_render.ceil_height = height(intersection_distance, 'C');
	data_render.wall_height = WINDOW_HEIGHT - data_render.ceil_height - data_render.floor_height;
	data_render.x = (int)(temp_angle / WIDTH_INTERVAL);
	data_render.x_winner = final.x_winner;
	data_render.y_winner = final.y_winner;
	
	return (data_render);
}

void	create_strip_helper(t_all *all, double temp_angle)
{
	double		ray_angle;
	t_winner	final;
	double		intersection_distance;
	t_render	data_render;
	
	ray_angle = under_full_circle(all->angle - (HAOV / 2) + temp_angle);
	final = find_winner(all, ray_angle);
	intersection_distance = calculate_distance(all, final, ray_angle, temp_angle);
	data_render = create_render_data(final, intersection_distance, temp_angle);
	init_strip(all, data_render);
}

void	create_strip(t_all *all)
{
	double	temp_angle;
	int		counter;

	temp_angle = 0;
	counter = 0;
	all->distance_flag = 0;
	all->left_distance = find_lateral_distance(all, 'L');
	all->right_distance = find_lateral_distance(all, 'R');
	while (counter <= NLOOP)
	{
		create_strip_helper(all, temp_angle);
		counter++;
		temp_angle+= WIDTH_INTERVAL;
	}
}

void render(t_all *all)
{
	create_strip(all);
	fill_index_strip(all);
	fill_length_strip(all);
	update_strips(all);
	strip_to_image(all);
}

t_all *init_all(char **argv)
{
	t_all *all;

	all = malloc(sizeof(t_all));
	if (!all)
		terminate(all, 1);
	ft_memset(all, 0, sizeof(t_all));
	all->argv = argv[1];
	all->fd = -1;
	all->map = map_parser(all);
	all->floor_color = color_maker(all, 'f');
	all->ceil_color = color_maker(all, 'c');
	all->x = start_loc_player(all, 'x');
	all->y = start_loc_player(all, 'y');
	all->angle = start_angle_player(all);
	all->max_distance = max_distance(all);	
	all->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT,	argv[0], false);
	if (!all->window)
		terminate(all, 1);
	all->north = image_maker(all, 'N');
	all->west = image_maker(all, 'W');
	all->south = image_maker(all, 'S');
	all->east = image_maker(all, 'E');
	return (all);
}

int main(int argc, char **argv)
{
	t_all *all;

	(void)argc;
	all = init_all(argv);
	render(all);
	mlx_key_hook(all->window, &press_key, all);	
	mlx_loop(all->window);
	terminate(all, 0);
}
