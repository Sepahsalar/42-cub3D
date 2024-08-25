/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nima <nnourine@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:43:59 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/25 15:15:37 by nima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// 1) clean minimap, player image

// 2) delete all conditions that includes loc->c == '1'

// 3) terminate, check failure, error -> combine (also reverse the order)

// 4) protect open close ...

// 5) resize the player image (either make it square or just resize it by 0.9)

// 6) delete or solve the problem of cloning mlx42 in Makefile

// 7) try to hide mlx42 realted valgrind errors (with .supp file)

// 8) mlx_get_time

// 9) find good material for walls

void	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("Invalid number of arguments", 2);
		ft_putendl_fd("Error", 2);
		exit (1);
	}
	if (!check_map_format(argv[1]))
	{
		ft_putendl_fd("Invalid map format", 2);
		ft_putendl_fd("Error", 2);
		exit (1);
	}
}

void	hooks_loops(t_all *all)
{
	mlx_key_hook(all->window, &keyboard, all);
	mlx_mouse_hook(all->window, &click, all);
	mlx_cursor_hook(all->window, &mouse, all);
	mlx_scroll_hook(all->window, &scroll, all);
	mlx_loop_hook(all->window, &animation, all);
	mlx_loop(all->window);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	check_args(argc, argv);
	all = init_all(argv);
	fill_strips(all);
	hooks_loops(all);
	terminate(all, 0);
}
