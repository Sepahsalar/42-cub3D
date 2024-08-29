/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:43:59 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/29 14:56:04 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Invalid number of arguments", 2);
		exit(1);
	}
	if (!check_map_format(argv[1]))
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Invalid map extension", 2);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_all	*all;

	check_args(argc, argv);
	all = init_all(argv);
	fill_strips(all);
	mlx_key_hook(all->window, &keyboard, all);
	mlx_loop(all->window);
	terminate(all, NULL, NULL, NULL);
}
