/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:43:59 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/22 12:05:21 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// terminate, check failure, error -> combine (also reverse the order)

// clean minimap

//protect open close ...

// try to hide mlx42 realted valgrind errors (with .supp file)

// resize the player image (either make it square or just resize it by 0.9)

// delete or solve the problem of cloning mlx42 in Makefile

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc != 2)
	{
		ft_putendl_fd("Invalid number of arguments", 2);
		ft_putendl_fd("Error", 2);
		return (1);
	}
	if (!check_map_format(argv[1]))
	{
		ft_putendl_fd("Invalid map format", 2);
		ft_putendl_fd("Error", 2);
		return (1);
	}
	// printf("main\n");
	all = init_all(argv);
	fill_strips(all);
	// enable_correct_player(all);
	mlx_key_hook(all->window, &press_key, all);
	mlx_loop(all->window);
	terminate(all, 0);
}
