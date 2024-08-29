/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:33:05 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/29 11:32:13 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static double	start_loc_player(t_all *all, char c)
{
	t_loc	*loc;

	loc = all->map->start;
	while (loc)
	{
		if (loc->c == 'N' || loc->c == 'S' || loc->c == 'W' || loc->c == 'E')
		{
			if (c == 'x')
				return (loc->x + 0.5);
			else
				return (loc->y + 0.5);
		}
		loc = loc->next;
	}
	return (-1);
}

static double	start_angle_player(t_all *all)
{
	t_loc	*loc;

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

void	image_loading(t_all *all)
{
	all->north = image_maker(all, 'N');
	all->west = image_maker(all, 'W');
	all->south = image_maker(all, 'S');
	all->east = image_maker(all, 'E');
	all->player_at_0 = image_maker(all, 'P');
	create_player_image(all);
	all->gun = image_maker(all, 'G');
	mlx_image_to_window(all->window, all->gun, START_GUN_X, START_GUN_Y);
	all->gun->instances[0].z = 3;
	all->blast = image_maker(all, 'B');
	mlx_image_to_window(all->window, all->blast, START_BLAST_X, START_BLAST_Y);
	all->blast->instances[0].z = 2;
	all->blast->instances[0].enabled = false;
	all->knife = image_maker(all, 'K');
	mlx_image_to_window(all->window, all->knife, 700, 810);
	all->knife->instances[0].z = 2;
	all->knife->instances[0].enabled = false;
	all->aim = image_maker(all, 'A');
	mlx_image_to_window(all->window, all->aim, 450, 450);
	all->aim->instances[0].enabled = true;
	all->aim->instances[0].z = 3;
}

void	check_necessary_textures(t_all *all)
{
	check_texture_exists(all, AIM_PATH);
	check_texture_exists(all, GUN_PATH);
	check_texture_exists(all, KNIFE_PATH);
	check_texture_exists(all, BLAST_PATH);
	check_texture_exists(all, PLAYER_PATH);
}

t_all	*init_all(char **argv)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	if (!all)
		terminate(all, "Allocating memory failed", NULL, NULL);
	ft_memset(all, 0, sizeof(t_all));
	all->argv = argv[1];
	all->map = map_parser(all);
	all->floor_color = color_maker(all, 'f');
	all->ceil_color = color_maker(all, 'c');
	all->x = start_loc_player(all, 'x');
	all->y = start_loc_player(all, 'y');
	all->angle = start_angle_player(all);
	all->max_distance = max_distance(all);
	remove_unnecessary_nodes(all);
	check_necessary_textures(all);
	all->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, argv[0], false);
	if (!all->window)
		terminate(all, "Initializing window failed", NULL, NULL);
	mlx_set_cursor_mode(all->window, MLX_MOUSE_HIDDEN);
	image_loading(all);
	mlx_get_mouse_pos(all->window, &all->x_mouse, &all->y_mouse);
	return (all);
}
